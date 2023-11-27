#include <SFML/Graphics.hpp>

using namespace sf;

void start();
void enterNumber(Event);
void enterN(Event);
void clickNextNumber();
void clickNextFN();
void clickNextSN();
void toNumber();
void toN(bool);
void toResult();
std::string calculate();
void reset();

int process = 0;
std::string number = "";
int fn = 0;
int sn = 0;
int minn = 2;

RenderWindow window(VideoMode(1000, 1000), L"Курсовая работа", Style::Titlebar | Style::Close);
Font font;
Text enterText("Enter the number", font, 70);
Text text("", font, 50);
Text nextText("Next step", font, 30);
RectangleShape shape(Vector2f(4000, 1));
RectangleShape next(Vector2f(200, 100));
RectangleShape back(Vector2f(200, 100));
Text backText("Back", font, 30);

int main()
{
    start();
    return 0;
}

void start() {
    window.setVerticalSyncEnabled(true);

    if (!font.loadFromFile("C:/Users/ibaev/source/repos/IbaevZA/font.ttf"))
    {
        return;
    }

    enterText.setPosition(20, 20);
    text.setPosition(20, 150);
    shape.setPosition(0, 203);
    next.setPosition(400, 850);
    nextText.setPosition(425, 880);

    shape.setFillColor(Color::Blue);
    next.setFillColor(Color::Blue);
    back.setFillColor(Color::Blue);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::TextEntered) {
                if (process == 1 || process == 2) {
                    enterN(event);
                }
                else if (process == 0) {
                    enterNumber(event);
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Vector2i mouse = Mouse::getPosition();
                Vector2i windowPosition = window.getPosition();
                Vector2f positionNext = next.getPosition();
                Vector2f positionBack = back.getPosition();
                Vector2f size = next.getSize();
                
                if ((process == 0 || process == 3) &&
                    mouse.x >= positionNext.x + windowPosition.x + 10 &&
                    mouse.x <= positionNext.x + size.x + windowPosition.x + 10 &&
                    mouse.y >= positionNext.y + windowPosition.y + 60 &&
                    mouse.y <= positionNext.y + size.y + windowPosition.y + 60) {
                    if (process == 0) {
                        clickNextNumber();
                    }
                    else {
                        reset();
                        toNumber();
                    }
                }
                else if ((process == 1 || process == 2) &&
                    mouse.x >= positionBack.x + windowPosition.x + 10 &&
                    mouse.x <= positionBack.x + size.x + windowPosition.x + 10 &&
                    mouse.y >= positionBack.y + windowPosition.y + 60 &&
                    mouse.y <= positionBack.y + size.y + windowPosition.y + 60) {
                    if (process == 1) {
                        minn = 2;
                        toNumber();
                    }
                    else {
                        toN(true);
                    }
                }
                else if ((process == 1 || process == 2) &&
                    mouse.x >= positionNext.x + windowPosition.x + 10 &&
                    mouse.x <= positionNext.x + size.x + windowPosition.x + 10 &&
                    mouse.y >= positionNext.y + windowPosition.y + 60 &&
                    mouse.y <= positionNext.y + size.y + windowPosition.y + 60) {
                    if (process == 1) {
                        clickNextFN();
                    }
                    else {
                        clickNextSN();
                    }
                }
            }
        }

        window.clear(Color::Black);
        if (process == 1 || process == 2) {
            window.draw(back);
            window.draw(backText);
        }
        window.draw(text);
        window.draw(shape);
        window.draw(enterText);
        window.draw(next);
        window.draw(nextText);
        window.display();
    }
}

void enterNumber(Event event) {
    if (event.text.unicode >= 48 && event.text.unicode <= 57 ||
        event.text.unicode >= 65 && event.text.unicode <= 70) {
        text.setString(text.getString() + event.text.unicode);
    }
    else if (event.text.unicode >= 97 && event.text.unicode <= 102)
    {
        text.setString(text.getString() + (event.text.unicode - 32));
    }
    else if (event.text.unicode == 8) {
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
    }
}

void enterN(Event event) {
    if (event.text.unicode >= 48 && event.text.unicode <= 57) {
        text.setString(text.getString() + event.text.unicode);
    }
    else if (event.text.unicode == 8) {
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
    }
}

void clickNextNumber() {
    if (text.getString() != "") {
        for (int i = 0; i < text.getString().getSize(); i++) {
            if (text.getString()[i] >= 'A') {
                minn = std::max(int(text.getString()[i] - 54), minn);
            }
        }
        number = text.getString();
        toN(true);
    }
}

void clickNextFN() {
    if (text.getString() == "")
        return;
    int ch = std::stoi(text.getString().toAnsiString());
    if (ch < minn || ch>16)
        return;
    fn = ch;
    toN(false);
}

void clickNextSN() {
    if (text.getString() == "")
        return;
    int ch = std::stoi(text.getString().toAnsiString());
    if (ch < 2 || ch>16) {
        return;
    }
    sn = ch;
    toResult();
}

void toN(bool isFirst) {
    text.setString("");
    if (isFirst) {
        process = 1;
        enterText.setString("Enter the number system");
        if(fn!=0)
            text.setString(std::to_string(fn));
    }
    else{
        process = 2;
        enterText.setString("Enter the desired number system");
        if (sn != 0)
            text.setString(std::to_string(sn));
    }
    next.setPosition(525, 850);
    back.setPosition(275, 850);
    nextText.setPosition(550, 880);
    backText.setPosition(345, 880);
}

void toNumber() {
    process = 0;
    enterText.setString("Enter the number");
    text.setString(number);
    nextText.setString("Next step");
    next.setPosition(400, 850);
    nextText.setPosition(425, 880);
}

void toResult() {
    process = 3;
    enterText.setString("Result");
    text.setString(calculate());
    nextText.setString("Restart");
    next.setPosition(400, 850);
    nextText.setPosition(445, 880);
}

void reset() {
    number = "";
    fn = 0;
    sn = 0;
    minn = 2;
    process = 0;
}

std::string calculate() {
    if (sn == fn) {
        return number;
    }
    return "";
}