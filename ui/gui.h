//
// Created by Juan Diego on 11/14/2022.
//

#ifndef BLOCK_CHAIN_GUI_H
#define BLOCK_CHAIN_GUI_H

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iomanip>
#include <vector>
#include <map>

#include "button.h"
#include "Blockchain.h"
#include "utils/unix.h"

enum class options {
    register_,
    login,
    close,
    showTransactions,
    showMenu,
    newTransaction
};

std::map<std::string, options> map{
        {"Login",    options::login},
        {"Close",    options::close},
        {"Register", options::register_}
};


class Gui {
private:
    sf::RenderWindow *window{};
    Blockchain *blockchain{};
    std::string sessionUsername{};
    std::string sessionPassword{};

public:
    explicit Gui() = default;

    virtual ~Gui() {
        delete window;
    }

    bool initialize(Blockchain *bch) {
        blockchain = bch;
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window = new sf::RenderWindow(
                sf::VideoMode((int) (desktop.width * 2.0 / 3.0), (int) (desktop.height * 2.0 / 3.0)), "BlockChain");
        window->setPosition(sf::Vector2<int>((int) (desktop.width / 2.0 - window->getSize().x / 2.0),
                                             (int) (desktop.height / 2.0 - window->getSize().y / 2.0)));
        return (window->isOpen() && blockchain);
    }

    void runLoop() {
        options option = this->showMenu();
        while (option != options::close) {
            switch (option) {
                case options::showMenu:
                    option = showMenu();
                    break;
                case options::login:
                    option = loginUser();
                    break;
                case options::register_:
                    option = registerUser();
                    break;
                case options::showTransactions:
                    option = showTransactions();
                    break;
                case options::newTransaction:
                    option = newTransaction();
                    break;
                default:
                    break;
            }
        }
        closeWindow();
    }

    options newTransaction() {
        Word messageUsername("Username to transfer:", 495, 180, 30, sf::Color::Yellow);
        Word messageAmount("Enter the amount:", 520, 330, 30, sf::Color::Yellow);

        Button Username(sf::Color::White, 500, 230, 50, 300, "", 25, sf::Color::Black);
        Button Amount(sf::Color::White, 500, 380, 50, 300, "", 25, sf::Color::Black);
        Button Send(sf::Color::Blue, 570, 470, 60, 160, "Transfer", 30, sf::Color::Yellow);
        Button Cancel(sf::Color::Red, 1120, 50, 50, 120, "Cancel", 25, sf::Color::Black);

        sf::Vector2 mousePosition = sf::Mouse::getPosition(*window);
        int actual_x, actual_y, prior_x, prior_y;

        while (window->isOpen()) {
            sf::Event event{};
            while (window->pollEvent(event)) {
                mousePosition = sf::Mouse::getPosition(*window);
                actual_x = mousePosition.x;
                actual_y = mousePosition.y;

                switch (event.type) {
                    case sf::Event::Closed:
                        return options::close;
                    case sf::Event::TextEntered:
                        if (event.text.unicode >= 128 || event.text.unicode <= 47) {
                            break;
                        }
                        if (Username.isOnBound(actual_x, actual_y)) {
                            Username.updateText(Username.getWord()->mensaje + static_cast<char>(event.text.unicode));
                        } else if (event.text.unicode >= 48 && event.text.unicode <= 57 &&
                                   Amount.isOnBound(actual_x, actual_y)) {
                            Amount.updateText(Amount.getWord()->mensaje + static_cast<char>(event.text.unicode));
                        }
                        break;
                    case sf::Event::KeyPressed:
                        switch (event.key.code) {
                            case sf::Keyboard::BackSpace:
                                if (Username.isOnBound(actual_x, actual_y)) {
                                    Username.deleteLastCharacter();
                                } else if (Amount.isOnBound(actual_x, actual_y)) {
                                    Amount.deleteLastCharacter();
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        if (Send.isOnBound(actual_x, actual_y)) {
                            Send.mouseEnterEvent(sf::Color::Yellow, sf::Color::Blue);
                        } else if (Send.isOnBound(prior_x, prior_y)) {
                            Send.mouseLeaveEvent(sf::Color::Blue, sf::Color::Yellow);
                        }
                        if (Cancel.isOnBound(actual_x, actual_y)) {
                            Cancel.mouseEnterEvent(sf::Color::Black, sf::Color::Red);
                        } else if (Cancel.isOnBound(prior_x, prior_y)) {
                            Cancel.mouseLeaveEvent(sf::Color::Red, sf::Color::Black);
                        }
                        prior_x = actual_x;
                        prior_y = actual_y;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (Send.isOnBound(actual_x, actual_y)) {
                            std::string to = Username.getWord()->mensaje;
                            std::string amount = Amount.getWord()->mensaje;
                            loadNewTransaction(this->sessionUsername, this->sessionPassword, to, amount);
                            return options::showTransactions;
                        } else if (Cancel.isOnBound(actual_x, actual_y)) {
                            return options::showTransactions;
                        }
                        break;
                    default:
                        break;
                }
            }

            window->clear();
            Username.draw(window);
            Amount.draw(window);
            Send.draw(window);
            Cancel.draw(window);
            window->draw(messageUsername.texto);
            window->draw(messageAmount.texto);
            window->display();
        }

        return {};
    }

    void loadNewTransaction(const std::string &from, const std::string &password, const std::string &to,
                            const std::string &amount) {
        time_t curr_time;
        curr_time = time(nullptr);

        tm *tm_local = localtime(&curr_time);
        auto unixTimestamp = timegm(tm_local);

        std::ofstream outTransactions("./assets/users/transactions.txt", std::ios_base::app);
        outTransactions << from << " " << password << " " << to << " " << amount << " " << unixTimestamp << std::endl;
        this->blockchain->setTx(from, password, to, std::stof(amount), std::to_string(unixTimestamp));
        outTransactions.close();
    }

    options showTransactions() {
        blockchain->myTxs(sessionUsername, sessionPassword);

        std::stringstream rowText;
        rowText << std::left << std::setw(15) << "sender" << std::left << std::setw(15) << "receiver" << std::left
                << std::setw(15) << "amount" << std::left << std::setw(15) << "full date";
        Word myTransactions("These are your completed transactions!", 350, 50, 30, sf::Color::Cyan);
        Word row(rowText.str(), 50, 160, 24, sf::Color::Cyan, "./assets/fonts/Anonymous_Pro.ttf");

        // Boton de logout
        Button LogOut(sf::Color::Red, 1120, 50, 50, 120, "Logout", 25, sf::Color::Black);

        // Boton de nueva transaccion
        Button newTransaction(sf::Color::Blue, 1000, 50, 50, 90, "New", 20, sf::Color::Yellow);

        // Botones del amount range
        Button amountRange(sf::Color::Green, 1000, 200, 50, 240, "Amount range", 25, sf::Color::Black);
        Button minAmount(sf::Color::White, 1000, 270, 50, 110, "", 20, sf::Color::Black, "./assets/fonts/Anonymous_Pro.ttf");
        Button maxAmount(sf::Color::White, 1130, 270, 50, 110, "", 20, sf::Color::Black, "./assets/fonts/Anonymous_Pro.ttf");

        // Botones del date range
        Button dateRange(sf::Color::Green, 1000, 340, 50, 240, "Date range d/m/y h:m:std", 16, sf::Color::Black);
        Button minDate(sf::Color::White, 1000, 410, 25, 240, "", 20, sf::Color::Black, "./assets/fonts/Anonymous_Pro.ttf");
        Button maxDate(sf::Color::White, 1000, 450, 25, 240, "", 20, sf::Color::Black, "./assets/fonts/Anonymous_Pro.ttf");

        // Boton de max amount
        Button topMaxAmount(sf::Color::Green, 1000, 500, 50, 110, "Max Amount", 17, sf::Color::Black);
        // Boton de min amount
        Button topMinAmount(sf::Color::Green, 1130, 500, 50, 110, "Min Amount", 17, sf::Color::Black);
        // Boton de max DATE
        Button topMaxDate(sf::Color::Green, 1000, 570, 50, 110, "Max Date", 17, sf::Color::Black);
        // Boton de min DATE
        Button topMinDate(sf::Color::Green, 1130, 570, 50, 110, "Min Date", 17, sf::Color::Black);

        sf::Vector2 mousePosition = sf::Mouse::getPosition(*window);
        int actual_x, actual_y, prior_x, prior_y;

        while (window->isOpen()) {
            sf::Event event{};
            while (window->pollEvent(event)) {
                mousePosition = sf::Mouse::getPosition(*window);
                actual_x = mousePosition.x;
                actual_y = mousePosition.y;

                switch (event.type) {
                    case sf::Event::Closed:
                        return options::close;
                    case sf::Event::TextEntered: {
                        char new_char = static_cast<char>(event.text.unicode);
                        if ((event.text.unicode >= 128 || event.text.unicode <= 46) && event.text.unicode != 32) {
                            break;
                        }

                        if (minDate.isOnBound(actual_x, actual_y)) {
                            minDate.updateText(minDate.getWord()->mensaje + new_char);
                        } else if (maxDate.isOnBound(actual_x, actual_y)) {
                            maxDate.updateText(maxDate.getWord()->mensaje + new_char);
                        }

                        if (event.text.unicode >= 58) {
                            break;
                        }
                        if (minAmount.isOnBound(actual_x, actual_y)) {
                            minAmount.updateText(minAmount.getWord()->mensaje + new_char);
                        } else if (maxAmount.isOnBound(actual_x, actual_y)) {
                            maxAmount.updateText(maxAmount.getWord()->mensaje + new_char);
                        }
                    }
                    case sf::Event::KeyPressed:
                        switch (event.key.code) {
                            case sf::Keyboard::BackSpace:
                                if (minAmount.isOnBound(actual_x, actual_y)) {
                                    minAmount.deleteLastCharacter();
                                } else if (maxAmount.isOnBound(actual_x, actual_y)) {
                                    maxAmount.deleteLastCharacter();
                                }
                                if (minDate.isOnBound(actual_x, actual_y)) {
                                    minDate.deleteLastCharacter();
                                } else if (maxDate.isOnBound(actual_x, actual_y)) {
                                    maxDate.deleteLastCharacter();
                                }
                                break;
                            default:
                                break;
                        }
                    case sf::Event::MouseMoved:
                        if (LogOut.isOnBound(actual_x, actual_y)) {
                            LogOut.mouseEnterEvent(sf::Color::Black, sf::Color::Red);
                        } else if (LogOut.isOnBound(prior_x, prior_y)) {
                            LogOut.mouseLeaveEvent(sf::Color::Red, sf::Color::Black);
                        }
                        if (newTransaction.isOnBound(actual_x, actual_y)) {
                            newTransaction.mouseEnterEvent(sf::Color::Yellow, sf::Color::Blue);
                        } else if (newTransaction.isOnBound(prior_x, prior_y)) {
                            newTransaction.mouseLeaveEvent(sf::Color::Blue, sf::Color::Yellow);
                        }
                        if (amountRange.isOnBound(actual_x, actual_y)) {
                            amountRange.mouseEnterEvent(sf::Color::Black, sf::Color::Green);
                        } else if (amountRange.isOnBound(prior_x, prior_y)) {
                            amountRange.mouseLeaveEvent(sf::Color::Green, sf::Color::Black);
                        }
                        if (dateRange.isOnBound(actual_x, actual_y)) {
                            dateRange.mouseEnterEvent(sf::Color::Black, sf::Color::Green);
                        } else if (dateRange.isOnBound(prior_x, prior_y)) {
                            dateRange.mouseLeaveEvent(sf::Color::Green, sf::Color::Black);
                        }
                        if (topMinAmount.isOnBound(actual_x, actual_y)) {
                            topMinAmount.mouseEnterEvent(sf::Color::Black, sf::Color::Green);
                        } else if (topMinAmount.isOnBound(prior_x, prior_y)) {
                            topMinAmount.mouseLeaveEvent(sf::Color::Green, sf::Color::Black);
                        }
                        if (topMaxAmount.isOnBound(actual_x, actual_y)) {
                            topMaxAmount.mouseEnterEvent(sf::Color::Black, sf::Color::Green);
                        } else if (topMaxAmount.isOnBound(prior_x, prior_y)) {
                            topMaxAmount.mouseLeaveEvent(sf::Color::Green, sf::Color::Black);
                        }
                        if (topMinDate.isOnBound(actual_x, actual_y)) {
                            topMinDate.mouseEnterEvent(sf::Color::Black, sf::Color::Green);
                        } else if (topMinDate.isOnBound(prior_x, prior_y)) {
                            topMinDate.mouseLeaveEvent(sf::Color::Green, sf::Color::Black);
                        }
                        if (topMaxDate.isOnBound(actual_x, actual_y)) {
                            topMaxDate.mouseEnterEvent(sf::Color::Black, sf::Color::Green);
                        } else if (topMaxDate.isOnBound(prior_x, prior_y)) {
                            topMaxDate.mouseLeaveEvent(sf::Color::Green, sf::Color::Black);
                        }
                        prior_x = actual_x;
                        prior_y = actual_y;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (LogOut.isOnBound(actual_x, actual_y)) {
                            this->sessionUsername.clear();
                            this->sessionPassword.clear();
                            return options::showMenu;
                        } else if (newTransaction.isOnBound(actual_x, actual_y)) {
                            return options::newTransaction;
                        } else if (amountRange.isOnBound(actual_x, actual_y)) {
                            blockchain->myTxsAmountRange(sessionUsername, sessionPassword,
                                                         std::stof(minAmount.getWord()->mensaje),
                                                         std::stof(maxAmount.getWord()->mensaje));
                            minAmount.updateText("");
                            maxAmount.updateText("");
                        } else if (dateRange.isOnBound(actual_x, actual_y)) {
                            std::string minimumDate = minDate.getWord()->mensaje;
                            std::string maximumDate = maxDate.getWord()->mensaje;
                            std::string minDateUnixTimestamp = dateToUnixTimestamp(minimumDate);
                            std::string maxDateUnixTimestamp = dateToUnixTimestamp(maximumDate);
                            blockchain->myTxsDateRange(sessionUsername, sessionPassword, minDateUnixTimestamp, maxDateUnixTimestamp);
                            minDate.updateText("");
                            maxDate.updateText("");
                        } else if (topMinAmount.isOnBound(actual_x, actual_y)) {
                            blockchain->myMinTxA(sessionUsername, sessionPassword);
                        } else if (topMaxAmount.isOnBound(actual_x, actual_y)) {
                            blockchain->myMaxTxA(sessionUsername, sessionPassword);
                        } else if (topMaxDate.isOnBound(actual_x, actual_y)) {
                            blockchain->myMaxTxD(sessionUsername, sessionPassword);
                        } else if (topMinDate.isOnBound(actual_x, actual_y)) {
                            blockchain->myMinTxD(sessionUsername, sessionPassword);
                        }
                        break;
                    default:
                        break;
                }
            }

            window->clear();
            window->draw(row.texto);
            LogOut.draw(window);
            newTransaction.draw(window);
            amountRange.draw(window);
            minAmount.draw(window);
            maxAmount.draw(window);
            dateRange.draw(window);
            minDate.draw(window);
            maxDate.draw(window);
            topMaxAmount.draw(window);
            topMinAmount.draw(window);
            topMaxDate.draw(window);
            topMinDate.draw(window);
            window->draw(myTransactions.texto);

            float x = 50;
            float y = 200;
            std::ifstream transactionsToShow("./assets/users/session.txt");
            std::string sender, reciever, amount, unixTimestamp;

            while (transactionsToShow >> sender >> reciever >> amount >> unixTimestamp) {
                std::time_t time_t_date(std::stol(unixTimestamp));
                std::string fullDate = std::asctime(std::gmtime(&time_t_date));

                std::stringstream ss_transaction;
                ss_transaction << std::left << std::setw(15) << sender << std::left << std::setw(15) << reciever
                               << std::left
                               << std::setw(15) << amount << std::left << std::setw(15)
                               << fullDate;
                Word transaction(ss_transaction.str(), x, y, 24, sf::Color::Yellow, "./assets/fonts/Anonymous_Pro.ttf");
                window->draw(transaction.texto);
                y += 50;
            }
            window->display();
        }
        return options::close;
    }

    void closeWindow() {
        std::cout << "closing window" << std::endl;
        window->close();
    }

    options loginUser() {
        Word messageUsername("Username:", 560, 180, 30, sf::Color::Yellow);
        Word messagePassword("Password:", 560, 330, 30, sf::Color::Yellow);

        Button Username(sf::Color::White, 500, 230, 50, 300, "", 25, sf::Color::Black);
        Button Password(sf::Color::White, 500, 380, 50, 300, "", 25, sf::Color::Black);
        Button Login(sf::Color::Blue, 570, 470, 60, 160, "Login", 30, sf::Color::Yellow);
        Button Back(sf::Color::Red, 1120, 50, 50, 100, "Back", 25, sf::Color::Black);

        sf::Vector2 mousePosition = sf::Mouse::getPosition(*window);
        int actual_x, actual_y, prior_x, prior_y;

        while (window->isOpen()) {
            sf::Event event{};
            while (window->pollEvent(event)) {
                mousePosition = sf::Mouse::getPosition(*window);
                actual_x = mousePosition.x;
                actual_y = mousePosition.y;

                switch (event.type) {
                    case sf::Event::Closed:
                        return options::close;
                    case sf::Event::TextEntered:
                        if (event.text.unicode >= 128 || event.text.unicode <= 47) {
                            break;
                        }
                        if (Username.isOnBound(actual_x, actual_y)) {
                            Username.updateText(Username.getWord()->mensaje + static_cast<char>(event.text.unicode));
                        } else if (Password.isOnBound(actual_x, actual_y)) {
                            Password.updateText(Password.getWord()->mensaje + static_cast<char>(event.text.unicode));
                        }
                        break;
                    case sf::Event::KeyPressed:
                        switch (event.key.code) {
                            case sf::Keyboard::BackSpace:
                                if (Username.isOnBound(actual_x, actual_y)) {
                                    Username.deleteLastCharacter();
                                } else if (Password.isOnBound(actual_x, actual_y)) {
                                    Password.deleteLastCharacter();
                                }
                            default:
                                break;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        if (Login.isOnBound(actual_x, actual_y)) {
                            Login.mouseEnterEvent(sf::Color::Yellow);
                        } else if (Login.isOnBound(prior_x, prior_y)) {
                            Login.mouseLeaveEvent(sf::Color::Blue);
                        }
                        if (Back.isOnBound(actual_x, actual_y)) {
                            Back.mouseEnterEvent(sf::Color::Black, sf::Color::Red);
                        } else if (Back.isOnBound(prior_x, prior_y)) {
                            Back.mouseLeaveEvent(sf::Color::Red, sf::Color::Black);
                        }
                        prior_x = actual_x;
                        prior_y = actual_y;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (Login.isOnBound(actual_x, actual_y)) {
                            this->sessionUsername = Username.getWord()->mensaje;
                            this->sessionPassword = Password.getWord()->mensaje;
                            return options::showTransactions;
                        } else if (Back.isOnBound(actual_x, actual_y)) {
                            return options::showMenu;
                        }
                    default:
                        break;
                }
            }

            window->clear();
            Back.draw(window);
            Login.draw(window);
            Username.draw(window);
            Password.draw(window);
            window->draw(messagePassword.texto);
            window->draw(messageUsername.texto);
            window->display();
        }

        return {};
    }

    options registerUser() {
        Word messageUsername("Register Username:", 500, 180, 30, sf::Color::Yellow);
        Word messagePassword("Register Password:", 500, 330, 30, sf::Color::Yellow);

        Button Username(sf::Color::White, 500, 230, 50, 300, "", 25, sf::Color::Black);
        Button Password(sf::Color::White, 500, 380, 50, 300, "", 25, sf::Color::Black);
        Button Register(sf::Color::Blue, 560, 470, 60, 170, "Register", 30, sf::Color::Yellow);
        Button Back(sf::Color::Red, 1120, 50, 50, 100, "Back", 25, sf::Color::Black);

        sf::Vector2 mousePosition = sf::Mouse::getPosition(*window);
        int actual_x, actual_y;
        int prior_x, prior_y;

        while (window->isOpen()) {
            sf::Event event{};
            while (window->pollEvent(event)) {
                mousePosition = sf::Mouse::getPosition(*window);
                actual_x = mousePosition.x;
                actual_y = mousePosition.y;

                switch (event.type) {
                    case sf::Event::Closed:
                        return options::close;
                    case sf::Event::TextEntered:
                        if (event.text.unicode >= 128 || event.text.unicode <= 47) {
                            break;
                        }
                        if (Username.isOnBound(actual_x, actual_y)) {
                            Username.updateText(Username.getWord()->mensaje + static_cast<char>(event.text.unicode));
                        } else if (Password.isOnBound(actual_x, actual_y)) {
                            Password.updateText(Password.getWord()->mensaje + static_cast<char>(event.text.unicode));
                        }
                        break;
                    case sf::Event::KeyPressed:
                        switch (event.key.code) {
                            case sf::Keyboard::BackSpace:
                                if (Username.isOnBound(actual_x, actual_y)) {
                                    Username.deleteLastCharacter();
                                } else if (Password.isOnBound(actual_x, actual_y)) {
                                    Password.deleteLastCharacter();
                                }
                            default:
                                break;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        if (Register.isOnBound(actual_x, actual_y)) {
                            Register.mouseEnterEvent(sf::Color::Yellow);
                        } else if (Register.isOnBound(prior_x, prior_y)) {
                            Register.mouseLeaveEvent(sf::Color::Blue);
                        }

                        if (Back.isOnBound(actual_x, actual_y)) {
                            Back.mouseEnterEvent(sf::Color::Black, sf::Color::Red);
                        } else if (Back.isOnBound(prior_x, prior_y)) {
                            Back.mouseLeaveEvent(sf::Color::Red, sf::Color::Black);
                        }
                        prior_x = actual_x;
                        prior_y = actual_y;
                        break;

                    case sf::Event::MouseButtonPressed:
                        if (Register.isOnBound(actual_x, actual_y)) {
                            std::string username = Username.getWord()->mensaje;
                            std::string password = Password.getWord()->mensaje;
                            loadToFile(username, password, "./assets/users/users.txt");
                            loadToBlockchain(username, password);
                            return options::showMenu;
                        } else if (Back.isOnBound(actual_x, actual_y)) {
                            return options::showMenu;
                        }
                    default:
                        break;
                }
            }

            window->clear();
            Register.draw(window);
            Username.draw(window);
            Password.draw(window);
            Back.draw(window);
            window->draw(messagePassword.texto);
            window->draw(messageUsername.texto);
            window->display();
        }

        return {};
    }

    static void loadToFile(const std::string &username, const std::string &password, const std::string &path) {
        std::ofstream outFile(path, std::ios_base::app);
        if (outFile.fail()) {
            std::cout << "error loading file: " << path << std::endl;
        }
        outFile << username << " " << password << std::endl;
        outFile.close();
    }

    void loadToBlockchain(const std::string &username, const std::string &password) {
        blockchain->createUser(username, password);
        std::cout << *blockchain << std::endl;
    }

    options showMenu() {
        sf::Vector2 size = window->getSize();
        std::vector<Button *> buttons;
        buttons.reserve(5);
        float largo, alto, x, y, textSize;
        std::string text;

        std::ifstream file("./assets/components/buttons.txt");
        std::getline(file, text);
        while (file >> x >> y >> largo >> alto >> text >> textSize) {
            buttons.push_back(new Button(sf::Color::Blue, x, y, alto, largo, text, textSize));
        }

        int actual_x, actual_y, prior_x, prior_y;
        sf::Vector2 mousePosition = sf::Mouse::getPosition(*window);

        while (window->isOpen()) {
            sf::Event event{};
            while (window->pollEvent(event)) {
                mousePosition = sf::Mouse::getPosition(*window);
                actual_x = mousePosition.x;
                actual_y = mousePosition.y;

                switch (event.type) {
                    case sf::Event::Closed:
                        return options::close;
                    case sf::Event::MouseMoved:
                        for (Button *&button: buttons) {
                            if (button->isOnBound(actual_x, actual_y)) {
                                button->mouseEnterEvent(sf::Color::Yellow);
                            } else if (button->isOnBound(prior_x, prior_y)) {
                                button->mouseLeaveEvent(sf::Color::Blue);
                            }
                        }
                        prior_x = actual_x;
                        prior_y = actual_y;
                        break;
                    case sf::Event::MouseButtonPressed:
                        for (Button *&button: buttons) {
                            if (button->isOnBound(actual_x, actual_y)) {
                                return map[button->getWord()->mensaje];
                            }
                        }
                    default:
                        break;
                }
            }

            window->clear();
            for (Button *&button: buttons) {
                button->draw(window);
            }
            window->display();
        }
        return {};
    }
};

#endif //BLOCK_CHAIN_GUI_H
