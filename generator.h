#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtWidgets>
#include <algorithm>

class Generator : public QObject
{
    Q_OBJECT
private:
    int** numbers;
    int difficulty;
    int counter;
    QVector<int> variants;
    QVector<int> buffer;
    QVector<int> wrongVariants;

public:
    explicit Generator(QObject *parent = 0);
    void recieveDifficulty(int diff);
    int startGeneration(int row);
    void fillVariants();
    int possibleVariant();
    void removeVariant(int v);
    void removeVariantsForCell(int I, int J);
    int oneVariantRemoving();
    int rowLastHeroRemoving(int I);
    int columnLastHeroRemoving(int J);
    void setWrongVariantsForCell(int I, int J);
};

#endif // GENERATOR_H
