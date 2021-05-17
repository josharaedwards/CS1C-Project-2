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
 * @class
 * @brief
 * @details
 */
class splashScreen : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     * @details
     * @param
     */
    explicit splashScreen(QWidget *parent = nullptr);
    /**
     * @brief
     * @details
     */
    ~splashScreen();

private:
    Ui::splashScreen *ui;   /// @var
};

#endif // SPLASHSCREEN_H
