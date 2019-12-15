#ifndef FM_PYTHON_H
#define FM_PYTHON_H

#include <QObject>
#include <QProcess>

class FM_Python : public QObject
{
    Q_OBJECT
public:
    explicit FM_Python(QObject *parent = nullptr);

    void execPython();
signals:

public slots:
    void Fctn_get_info();
private:
    QProcess *process;

};

#endif // FM_PYTHON_H
