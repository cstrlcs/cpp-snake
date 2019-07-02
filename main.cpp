#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main(){
    //inicialização da janela
    sf::RenderWindow window(sf::VideoMode(832,832), "cobrinha");
    sf::Clock clock;

    //gera uma semente aleatória para o rand
    srand(time(NULL));

    //define o tamanho e inicializa a cobra (vetor de esferas)
    int length = 1;
    std::vector<sf::CircleShape> snake(100);

    //define o raio e a cor da cabeça
    snake[0] = sf::CircleShape(16);
    snake[0].setFillColor(sf::Color::Red);

    //direção inicial da cabeça
    sf::Vector2f dir(0,32);

    //inicializa a comida em uma posição aleatória dentro do grid (32x32 * 26)
    sf::CircleShape food(10);
    food.setFillColor(sf::Color::Green);
    food.setPosition(sf::Vector2f(32*(1+rand()%20), 32*(1+rand()%20)));
   
    //renderiza frame a frame
    while(window.isOpen()){
        sf::Event event;
        
        while(window.pollEvent(event)){
            //detecta se o usuário fechou a janela
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //limpa a tela com a coloração preta
        window.clear(sf::Color::Black);

            //DRAW

        //altera a direção da cobra ao apertar uma arrow key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dir = sf::Vector2f(-32,0);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir = sf::Vector2f(32,0);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dir = sf::Vector2f(0,-32);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dir = sf::Vector2f(0,32);

        //checa se a cobra chegou até a comida, caso sim, move para outra posição aleatória
        if (snake[0].getPosition()== food.getPosition()){
            food.setPosition(sf::Vector2f(32*(1+rand()%20), 32*(1+rand()%20)));
            //inicializa um novo componente da cobra e o posiciona temporariamente fora da tela
            snake[length] = sf::CircleShape(12);
            snake[length].setFillColor(sf::Color::Red);
            snake[length].setPosition(Vector2f(-32,-32));
            length++;
        }

        //define a taxa de atualização de quadros (clock)
        if (clock.getElapsedTime().asSeconds() > 0.1f){
            //repassa cada um dos componentes da cobra de trás para frente
            for (int i=length-1; i>0; i--){
                //caso a cobra encoste em algum componente, acaba o jogo
                if (snake[0].getPosition() == snake[i].getPosition() && i != 0)
                    window.close();
                
                //cria uma espécie de recursão -> o último componente vai para a posição do antepenúltimo e assim vai
                snake[i].setPosition(snake[i-1].getPosition());
            }
            //aplica a movimentação e reinicia o relógio
            snake[0].move(dir);
            clock.restart();
        }
        window.draw(food);
        //window.draw(snake[0]);
        //desenha na tela os componentes da cobra
        for (int i=0; i<length; i++) window.draw(snake[i]);

        window.display();
    }

    return 0;
}