#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>

class BinaryConverter : public QWidget {
    Q_OBJECT

public:
    BinaryConverter(QWidget *parent = nullptr) : QWidget(parent) {
        numberLabel = new QLabel("Выбранное число:", this);
        numberSlider = new QSlider(Qt::Horizontal, this);
        numberSlider->setRange(1, 99);

        convertButton = new QPushButton("Перевести в двоичную", this);
        resultLabel = new QLabel("Результат:", this);

        connect(convertButton, &QPushButton::clicked, this, &BinaryConverter::convertToBinary);
        connect(numberSlider, &QSlider::valueChanged, this, &BinaryConverter::updateNumberLabel);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(numberLabel);
        layout->addWidget(numberSlider);
        layout->addWidget(convertButton);
        layout->addWidget(resultLabel);

        setLayout(layout);
    }

public slots:
    void convertToBinary() {
        int decimalNumber = numberSlider->value();
        QString binaryResult = QString::number(decimalNumber, 2);
        resultLabel->setText("Результат: " + binaryResult);
    }

    void updateNumberLabel() {
        int sliderValue = numberSlider->value();
        numberLabel->setText("Выбранное число: " + QString::number(sliderValue));
    }

private:
    QLabel *numberLabel;
    QSlider *numberSlider;
    QPushButton *convertButton;
    QLabel *resultLabel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BinaryConverter binaryConverter;
    binaryConverter.show();

    return app.exec();
}

#include "main.moc"
