/**
 * @file Alert.h
 * @author hankm
 *
 * A class that displays moving alerts.
 */

#ifndef PROJECT1_SUDOKULIB_ALERT_H
#define PROJECT1_SUDOKULIB_ALERT_H

/**
 * A class that displays moving alerts.
 */
class Alert
{
private:
    /// The message to display.
    std::wstring mMessage;

    /// The row the message is currently at.
    double mHeight;

public:
    /// Default constructor (disabled)
    Alert() = delete;

    /// Copy constructor (disabled)
    Alert(const Alert &) = delete;

    /// Assignment operator
    void operator=(const Alert &) = delete;

    /// Constructor
    Alert(std::wstring message, int height);

    ///Draws message
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width);

    void Update(double elapsed);
    bool ReadyForDelete();
};

#endif //PROJECT1_SUDOKULIB_ALERT_H
