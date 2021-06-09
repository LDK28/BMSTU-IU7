#include "rc.h"
#include <QMessageBox>

void print_warning(rc_type rc)
{
    if (rc == OK)
        return;
    QMessageBox mbox;
    if (rc == ERR_OPEN_FILE)
    {
        mbox.setText("При открытии файла произошла ошибка. Попробуйте еще раз.");
    }
    else if (rc == ERR_EMPTY)
    {
        mbox.setText("Пустая модель. Невозможно нарисовать.");
    }
    else if (rc == ERR_INPUT)
    {
        mbox.setText("INPUT");
    }
    else if (rc == ERR_MEMORY)
    {
        mbox.setText("MEMORY");
    }
    else if (rc == ERR_PARAMETR)
    {
        mbox.setText("PARAMETR");
    }
    else
    {
        mbox.setText("UNKNOWN ERROR");
    }
    mbox.exec();
}
