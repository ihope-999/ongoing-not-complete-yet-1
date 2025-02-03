#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <tuple>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>  
#include <fstream>
#include <cmath>


struct circle_elements{
    sf::VertexArray circle_element;
    float sx;
    float sy;


};
struct bullet_elements {
    sf::CircleShape bullet;
    float sx;
    float sy;

};

struct Bullet {
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;float S;


};


void draw_bullets(sf::RenderWindow& window, std::vector<bullet_elements>& bullet_elements) {
    for (auto& bullet : bullet_elements) {
            window.draw(bullet.bullet);
    }
}
template<typename T>
void create(sf::VertexArray& circle,T&SR) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        int randomm = std::rand() % 250;
        for (size_t i = 0; i < circle.getVertexCount(); i++) {
            float angle = i * 3.14 / circle.getVertexCount();
            circle[i].position = sf::Vector2f(SR * std::cos(angle) + randomm, SR * std::sin(angle) + randomm);
            circle[i].color = sf::Color::Red;
            std::cout << circle[i].position.y;


        }
        std::cout << "the random is " << randomm << std::endl;

    }

template<typename T>
class VECTOR {

public:
    T x;
    T y;
    VECTOR(const T& xm, const T& ym) : x(xm), y(ym) {}
    VECTOR(sf::Vector2<T>& vectors) :x(vectors.x), y(vectors.y) {}
    VECTOR() = default;

    VECTOR operator + (const VECTOR& vector) {
        return VECTOR(x + vector.x, y + vector.y);

    }
    VECTOR operator - (const VECTOR& vector) {
        return VECTOR(x - vector.x, y - vector.y);

    }
    VECTOR operator * (const VECTOR& vector) {
        return VECTOR(x * vector.x, y * vector.y);

    }
    VECTOR operator / (const VECTOR& vector) {
        return VECTOR(x / vector.x, y / vector.y);

    }

    VECTOR operator += (const VECTOR& vector) {
        return VECTOR(x + vector.x, y + vector.y);
    }
    VECTOR operator = (const VECTOR& vector) {
        return VECTOR(vector.x, vector.y);
    }
    void coordinates() {
        std::cout << x << " " << y << std::endl;
    }
};

sf::Vector2f center_finder(sf::VertexArray&circle) {
    float my_x_center = 0.0f;
    float my_y_center = 0.0f;
        for (size_t i = 0; i < circle.getVertexCount(); i++) {
            my_x_center += circle[i].position.x;
            my_y_center += circle[i].position.y;

        }
        my_x_center /= circle.getVertexCount();
        my_y_center /= circle.getVertexCount();
        sf::Vector2f center (my_x_center, my_y_center);
        return center;

    }


template <typename T>

void LoadFromFile(const std::string& filename, T& SR, T& CR, T& FR, T& FG, T& FB, T& OR, T& OG, T& OB, T& V, T& S) {
    std::ifstream fin(filename);
    std::string name;
    while (fin >> name) {
        if (name == "Circle" || name == "Player" || name == "Bullet")
        {
            fin >> SR >> CR >> FR >> FG >> FB >> OR >> OG >> OB >> V >> S;
            break;
        }


    }
}
class Bullets {
public:
    float SR, CR, FR, FG, FB, OR, OG, OB, sx, sy;
    Bullets() {

        LoadFromFile("C:/Users/anime/OneDrive/Masaüstü/game_file_info.txt", SR, CR, FR, FG, FB, OR, OG, OB, sx, sy);
        sf::CircleShape bullet;
        bullet.setRadius(SR);
    }






};
float distance(sf::Vector2f&d1,sf::Vector2f&d2) {
    float real_distance = sqrt(((d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y)));
    return real_distance;
}
void check_collisions(sf::CircleShape& me,std::vector<circle_elements>& allentity) {
    sf::Vector2f center;
    center = me.getPosition();
    
    center += sf::Vector2f(me.getRadius(), me.getRadius());
    for (auto& circle : allentity) {
        float my_x_center = 0.0f;
        float my_y_center = 0.0f;
        for (size_t i = 0; i < circle.circle_element.getVertexCount(); i++) {
            my_x_center+= circle.circle_element[i].position.x  ;
            my_y_center += circle.circle_element[i].position.y ;
        }
        my_x_center /= circle.circle_element.getVertexCount();
        my_y_center /= circle.circle_element.getVertexCount();

        sf::Vector2f my_real_center = sf::Vector2f(my_x_center , my_y_center );
        float distancee = distance(my_real_center, center);
        if (distancee-15 < 2 * me.getRadius()) {
            std::cout << "collision happened" << std::endl;
            circle.sx = -circle.sx;
            circle.sy = -circle.sy;
        }

    }

}

void check_my_movements(sf::Event& event, float& me_x, float& me_y) {
    float SR, CR, FR, FG, FB, OR, OG, OB, sx, sy;

    LoadFromFile("C:/Users/anime/OneDrive/Masaüstü/game_file_info.txt", SR, CR, FR, FG, FB, OR, OG, OB, sx, sy);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            me_y -= sy;
            std::cout << " w is pressed" << std::endl ;
        }
        if (event.key.code == sf::Keyboard::S) {
            me_y +=sy;
        }
        if (event.key.code == sf::Keyboard::D) {
            me_x += sx;
        }
        if (event.key.code == sf::Keyboard::A) {
            me_x -= sx;
        }
    }
}
template <typename T>
class CShape{
public:
    using Component_c = std::vector<sf::VertexArray>;
    
    Component_c circles;
    T randomm,random,random_x,random_y,SR, CR, FR, FG, FB, OR, OG, OB, sx, sy;
    
    
    CShape() {
    LoadFromFile("C:/Users/anime/OneDrive/Masaüstü/game_file_info.txt", SR, CR, FR, FG, FB, OR, OG, OB, sx, sy);
    
    }
   
    
    void finder(sf::VertexArray& circle, time_t& now, time_t& past, T& random) {

        if (now - past >= 3)
        {
            
            std::cout << "\n" << "time passed: " << now - past << "\n";
            past = now;
            switch (random) {
            case 3:
                circle.setPrimitiveType(sf::Triangles);
                circle.resize(3);
                std::cout << "\n" << "3 is the one" << "\n";
                break;

            case 4:
                circle.setPrimitiveType(sf::Quads);
                circle.resize(4);
                std::cout << "\n" << "4 is the one" << "\n";


                break;
            case 5:
                circle.setPrimitiveType(sf::TrianglesFan);
                circle.resize(5);
                std::cout << "\n" << "5 is the one" << "\n";


                break;
            default:
                circle.setPrimitiveType(sf::TrianglesFan);
                circle.resize(55);
                std::cout << "\n" << "Circle is the one" << "\n";


                break;

            }
            create(circle, SR);
            
        }
    }
    

    void check_positions(std::vector<circle_elements>&circles,T& WIDTH, T& HEIGHT) {
        for (auto& circle : circles) 
        {
            for (size_t i = 0; i < circle.circle_element.getVertexCount(); i++)
            {
                sf::Vector2f center = center_finder(circle.circle_element);
                if ( center.y  + 10.5f> HEIGHT)
            
            {
                circle.sy = -circle.sy;
            }
                else if (center.x + 10.5f > WIDTH) {
                    circle.sx = -circle.sx;

                }
                    
                else if (center.x < 10.5f) {
                    circle.sx = -circle.sx;                
                }
                else if (center.y < 10.5f) {
                    circle.sy = -circle.sy;
                }
                
            }
        }
    }
    void move_circles(std::vector<circle_elements>&circles) {
        for (auto& circle : circles) {
            for (size_t i = 0; i < circle.circle_element.getVertexCount(); i++) {
                circle.circle_element[i].position += sf::Vector2f(circle.sx, circle.sy);


            }
        }
    }
    void draw(std::vector<circle_elements>&circles,sf::RenderWindow & window) {
        for (auto& circle : circles)
        {
            window.draw(circle.circle_element);
        }
        }

  
};





template<typename T>
class EntityManager {
    using Allentities = std::vector<circle_elements >;
    using Allentities_bullet = std::vector<bullet_elements>;

public:
    Allentities allentities;
    Allentities_bullet allentities_bullet;
    EntityManager() {};

    void addentity(circle_elements& circle_element) {
        allentities.push_back(circle_element);
        std::cout << "ther size is" << allentities.size() << std::endl;;
    }
    void addentity_bullet(bullet_elements& bullet_element) {
        allentities_bullet.push_back(bullet_element);
    }
};
void attack(sf::CircleShape&bullet, sf::CircleShape& me,sf::RenderWindow&window,sf::Event& event,float&me_x , float&me_y) {
    if (event.type == sf::Event::MouseButtonPressed) {
        bullet.setRadius(5);
        bullet.setPosition(me_x, me_y);
        sf::Vector2f position_to_begin = sf::Vector2f(me_x, me_y);
        sf::Vector2f position_to_end = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        float real_distance = distance(position_to_begin, position_to_end);
        float x_diffs = abs(event.mouseButton.x - me_x);
        float sx = 0.0015 * std::cos(atan2(event.mouseButton.y - me_y, event.mouseButton.x -me_x));
        float sy = 0.0015 * std::sin(atan2(event.mouseButton.y - me_y, event.mouseButton.x - me_x));
        std::cout << "sx is : " << sx << std::endl;
        std::cout << "sy is  " << sy << std::endl;
        while (real_distance >10 ) {
            sf::Vector2f position_to_end = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            real_distance -= sqrt(sx * sx + sy * sy);
            bullet.move(sx, sy);

        }
    }
}
int main() {
    EntityManager<float> allentity;
    Bullets bullets;

    int WIDTH = 1200;
    int HEIGHT = 800;
    int frame = 0;
    float me_radius = 50;
    float me_x = 40;
    float me_y = 30;
    time_t currenttime;
    currenttime = time(nullptr);
    int r, t, y;
    r = 3;
    t = 4;
    y = 3;

    sf::CircleShape me;
    sf::CircleShape bullet;
    me.setRadius(me_radius);
    CShape<int> CIRCLE;
    sf::RenderWindow window(sf::VideoMode (WIDTH,HEIGHT), "mytitle");
    while (window.isOpen()) {
        time_t now;
        now = time(nullptr);

        me.setPosition(me_x, me_y);

        std::srand((static_cast<unsigned int> (std::time(0))));
        int random = std::rand() % 6;
        int random_x = std::rand() % 500;
        int random_y = std::rand() % 555;
        if (frame%180 == 0) {
            std::cout << "new item ";
            sf::VertexArray circle;
            bullet.setRadius(5);
            Bullets bullets;
            
            float sx = 5.2f;
            float sy = 5.2f;
            CIRCLE.finder(circle, now, currenttime,random);
            struct circle_elements circle_elements = { circle, sx, sy };
            CIRCLE.circles.push_back(circle);
            allentity.addentity(circle_elements);

           


        }
        sf::Event event;
       
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            check_my_movements(event, me_x, me_y);
            attack(bullet,me, window,event,me_x, me_y);

        }   
      
       

        window.setFramerateLimit(70);
        window.clear();
        CIRCLE.move_circles(allentity.allentities);

        CIRCLE.check_positions(allentity.allentities,WIDTH, HEIGHT);
        check_collisions(me, allentity.allentities);

        window.draw(me);
        window.draw(bullet);
        CIRCLE.draw(allentity.allentities,window);
        draw_bullets(window, allentity.allentities_bullet);
        window.display();

        frame++;
    }


    return 0;
}