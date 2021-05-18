/**
 *  @file splashscreen.h
 *  @brief Contains the definition of the splashScreen window
 */

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDialog>

namespace Ui {
class splashScreen;
}

/**
 * @class splashScreen
 * @brief splashScreen class shows an opening animation before program startup
 * @details is a frameless window, press esc to exit and start program
 */
class splashScreen : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief splashscreen constructor
     * @details creates and lays out splashscreen
     */
    explicit splashScreen(QWidget *parent = nullptr);
    /**
     * @brief splashScreen destructor
     * @details exits out of the splashscreen
     */
    ~splashScreen();

private:
    Ui::splashScreen *ui;   /// @var ui pointer representing splashScreen ui
};

#endif // SPLASHSCREEN_H
