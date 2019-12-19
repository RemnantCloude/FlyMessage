#ifndef FM_PYTHON_H
#define FM_PYTHON_H

#include <QObject>
#include <QProcess>

class FM_Python : public QObject
{
    Q_OBJECT
public:
    explicit FM_Python(QObject *parent = nullptr);
    ~FM_Python(){}

signals:
    void pythonEnd(QString website);
public slots:
    void getClawlerOutput();
    void execPython(QStringList websitelist);
private:
    QProcess *process;

};

#endif // FM_PYTHON_H
