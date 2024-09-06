#ifndef UIFORM_H
#define UIFORM_H

#include <QWidget>

namespace Ui {
class Form;
}

/**
 * @class UiForm
 * @brief Klasa reprezentująca formularz interfejsu użytkownika.
 *
 * Klasa `UiForm` dziedziczy po `QWidget` i jest używana do zarządzania
 * interfejsem użytkownika w aplikacji.
 */
class UiForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy UiForm.
     * @param parent Wskaźnik na rodzica klasy `QWidget`, domyślnie ustawiony na nullptr.
     */
    explicit UiForm(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy UiForm.
     *
     * Destruktor zwalnia zasoby używane przez obiekt `Ui::Form`.
     */
    ~UiForm();

private:
    Ui::Form *ui; /**< Wskaźnik na obiekt klasy `Ui::Form`, zarządzający elementami interfejsu. */
};

#endif // UIFORM_H
