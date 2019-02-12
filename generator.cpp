#include "generator.h"
#include "widget.h"

extern Widget* widget;

Generator::Generator(QObject *parent) : QObject(parent)
{
    counter = 0;
    numbers = new int*[9];
    for(int i = 0; i < 9; i++)
        numbers[i] = new int [9];
}

void Generator::recieveDifficulty(int diff)
{
    difficulty = diff;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            numbers[i][j] = 0;
    startGeneration(0);
    oneVariantRemoving();
    for(int i = 0; i < 9; i++)
        if(i%difficulty == 0)
            rowLastHeroRemoving(i);
    for(int j = 0; j< 9; j++)
        if(j%difficulty == 0)
            rowLastHeroRemoving(j);

    widget->recievePuzzle(numbers);
}

int Generator::startGeneration(int row)
{
    counter++;
    for(int I = row; I < 9; I++)
    {
        for(int J = 0; J < 9; J++)
        {
            removeVariantsForCell(I, J);
            if(variants.empty())
            {
                if (counter == 5)
                {
                    counter = 0;
                    for(int n = 0; n < 9; n++)
                    {
                        numbers[I][n] = 0;
                        numbers[I-1][n] = 0;
                    }
                    startGeneration(I-1);
                }
                else
                    startGeneration(I);
                return 0;
            }
            else
                numbers[I][J] = possibleVariant();
        }
     }
     counter = 0;
     return 1;
}

void Generator::fillVariants()
{
    variants.clear();
    for(int i = 1; i <= 9; i++)
        variants.push_back(i);
}

int Generator::possibleVariant()
{
    return variants[rand()%variants.size()];
}

void Generator::removeVariant(int v)
{
    for(int i = 0; i < variants.size(); i++)
        if(variants[i] == v)
            variants.erase(variants.begin()+i);
}

void Generator::removeVariantsForCell(int I, int J)
{
    fillVariants();
    for(int i = 0; i < 9; i++)
        removeVariant(numbers[i][J]);
    for(int j = 0; j < 9; j++)
         removeVariant(numbers[I][j]);
    for(int i = I-(I%3); i < (I/3)*3+3; i++)
        for(int j = J-(J%3); j < (J/3)*3+3; j++)
            removeVariant(numbers[i][j]);
}

int Generator::oneVariantRemoving()
{
    int I = rand()%9;
    int J = rand()%9;
    int temp = numbers[I][J];
    numbers[I][J] = 0;
    for(int i = 0 ; i < 9; i++)
        for(int j = 0 ; j < 9; j++)
        {
            fillVariants();
            removeVariantsForCell(i, j);
            if(variants.size() > 1)
            {
                numbers[I][J] = temp;
                counter++;
            }
        }
    if(counter > 100)
    {
        counter = 0;
        return 0;
    }
    oneVariantRemoving();
    return 1;
}

int Generator::rowLastHeroRemoving(int I)
{
    int J = rand()%9;
    while(numbers[I][J] == 0)
        J = rand()%9;
    int oldValue = numbers[I][J];
    numbers[I][J] = 0;
    removeVariantsForCell(I, J);
    buffer.clear();
    buffer = variants;
    for(int j = 0; j < 9; j++)
    {
        if(j != J && numbers[I][j] == 0)
        {
            QVector<int> temp;
            setWrongVariantsForCell(I, j);
            std::set_intersection(buffer.begin(), buffer.end(),
                             wrongVariants.begin(), wrongVariants.end(),
                             std::back_inserter(temp));
            buffer = temp;
        }
    }
    if(buffer.size() != 1)
    {
        numbers[I][J] = oldValue;
        counter++;
        if(counter > 100)
        {
            counter = 0;
            return 0;
        }
    }
    else
        counter = 0;
    rowLastHeroRemoving(I);
    return 1;
}

int Generator::columnLastHeroRemoving(int J)
{
    int I = rand()%9;
    while(numbers[I][J] == 0)
        I = rand()%9;
    int oldValue = numbers[I][J];
    numbers[I][J] = 0;
    removeVariantsForCell(I, J);
    buffer.clear();
    buffer = variants;
    for(int i = 0; i < 9; i++)
    {
        if(i != I && numbers[i][J] == 0)
        {
            QVector<int> temp;
            setWrongVariantsForCell(i, J);
            std::set_intersection(buffer.begin(), buffer.end(),
                             wrongVariants.begin(), wrongVariants.end(),
                             std::back_inserter(temp));
            buffer = temp;
        }
    }
    if(buffer.size() != 1)
    {
        numbers[I][J] = oldValue;
        counter++;
        if(counter > 100)
        {
            counter = 0;
            return 0;
        }
    }
    else
        counter = 0;
    columnLastHeroRemoving(J);
    return 1;
}

void Generator::setWrongVariantsForCell(int I, int J)
{
    removeVariantsForCell(I, J);
    QVector<int> temp = variants;
    fillVariants();
    wrongVariants.clear();
    std::set_difference(variants.begin(), variants.end(),
                   temp.begin(), temp.end(),
                   std::inserter(wrongVariants,
                   wrongVariants.begin()));
}
