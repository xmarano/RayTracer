// main.cpp
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

// Structure pour transporter un pixel
struct Pixel {
    unsigned int x, y;
    sf::Color color;
};

std::queue<Pixel>      pixelQueue;
std::mutex             mtx;
std::condition_variable cv;
bool                   productionDone = false;

// Thread #1 : production des pixels
void producer()
{
    const unsigned int W = 1000, H = 1000;
    const unsigned int total = W * H;
    for (unsigned int idx = 0; idx < total; ++idx) {
        unsigned int x = idx % W;
        unsigned int y = idx / W;
        sf::Uint8 v = static_cast<sf::Uint8>( idx * 255 / (total - 1) );
        Pixel p{ x, y, sf::Color(v, v, v) };

        {
            std::lock_guard<std::mutex> lock(mtx);
            pixelQueue.push(p);
        }
        cv.notify_one();

        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        productionDone = true;
    }
    cv.notify_one();
}

// Boucle SFML — **doit tourner dans le thread principal**
void consumerMainThread()
{
    const unsigned int W = 1000, H = 1000;
    sf::RenderWindow window(sf::VideoMode(W, H), "Threaded SFML Display");
    sf::Image   image; image.create(W, H, sf::Color::Black);
    sf::Texture texture; texture.loadFromImage(image);
    sf::Sprite  sprite(texture);

    while (window.isOpen()) {
        // 1) Gestion des événements
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 2) Récupération des pixels produits
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{
                return !pixelQueue.empty() || productionDone;
            });

            while (!pixelQueue.empty()) {
                Pixel p = pixelQueue.front();
                pixelQueue.pop();
                image.setPixel(p.x, p.y, p.color);
            }
        }

        // 3) Mise à jour et affichage
        texture.loadFromImage(image);
        window.clear();
        window.draw(sprite);
        window.display();

        // 4) Si terminé, fermer après 1 s
        std::lock_guard<std::mutex> lock(mtx);
        if (productionDone && pixelQueue.empty()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            window.close();
        }
    }
}

int main()
{
    // 1) On lance le producteur dans un thread secondaire
    std::thread prod(producer);

    // 2) On exécute la boucle SFML dans le thread principal
    consumerMainThread();

    // 3) On attend la fin du producteur avant de quitter
    if (prod.joinable())
        prod.join();

    return 0;
}
