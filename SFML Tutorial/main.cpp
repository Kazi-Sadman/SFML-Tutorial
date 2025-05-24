#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;


const int WIDTH = 800;
const int HEIGHT = 800;
const int NUM_STARS = 500;
const float MAX_DEPTH = 2000.0f;
const float FOCAL_LENGTH = 300.0f;


struct Star {
    float x, y, z;
    float speed;
    CircleShape shape;
};

vector<Star> stars(NUM_STARS);


void initializeStars()
{
    srand(time(NULL));
    for (auto& star : stars) {
        star.x = (rand() % (WIDTH * 2)) - WIDTH;
        star.y = (rand() % (HEIGHT * 2)) - HEIGHT;
        star.z = (rand() % static_cast<int>(MAX_DEPTH)) + 1;
        star.speed = 1.0f + (rand() % 100) / 50.0f;  // 1.0 - 3.0

        star.shape.setRadius(2.0f);
        star.shape.setFillColor(Color::White);
        //star.shape.setOrigin(2.0f, 2.0f); 
    }
}

void updateStars() {
    for (auto& star : stars) {
        star.z -= star.speed;


        if (star.z <= 0 ||
            star.shape.getPosition().x < 0 ||
            star.shape.getPosition().x > WIDTH ||
            star.shape.getPosition().y < 0 ||
            star.shape.getPosition().y > HEIGHT)
        {
            star.x = (rand() % (WIDTH * 2)) - WIDTH;
            star.y = (rand() % (HEIGHT * 2)) - HEIGHT;
            star.z = MAX_DEPTH;
            star.speed = 1.0f + (rand() % 100) / 50.0f;
        }

        // 3D ???? 2D ????????
        float depthFactor = FOCAL_LENGTH / star.z;
        float screenX = star.x * depthFactor + WIDTH / 2;
        float screenY = star.y * depthFactor + HEIGHT / 2;

        // ????? ????? ??? ????
        star.shape.setPosition(screenX, screenY);
        star.shape.setRadius(2.0f * depthFactor);
        star.shape.setOrigin(
            star.shape.getRadius(),
            star.shape.getRadius()
        );
    }
}


void controlPlane(CircleShape& plane) {
    float moveSpeed = 3.0f;
    if (Keyboard::isKeyPressed(Keyboard::A))
        plane.move(-moveSpeed, 0);
    if (Keyboard::isKeyPressed(Keyboard::D))
        plane.move(moveSpeed, 0);
    if (Keyboard::isKeyPressed(Keyboard::W))
        plane.move(0, -moveSpeed);
    if (Keyboard::isKeyPressed(Keyboard::S))
        plane.move(0, moveSpeed);
}

int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "3D Star Field");
    window.setFramerateLimit(60);


    CircleShape plane(20.f, 3);
    plane.setPosition(WIDTH / 2, HEIGHT / 2 + 200);
    plane.setFillColor(Color::Green);
    //plane.setOrigin(20.f, 20.f);


    initializeStars();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        window.clear(Color::Black);

        updateStars();
        controlPlane(plane);


        for (const auto& star : stars) {
            window.draw(star.shape);
        }

        window.draw(plane);
        window.display();
    }

    return 0;
}





