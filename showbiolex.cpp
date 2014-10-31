#include "showbiolex.h"
#include "ui_showbiolex.h"
#include <QTextBrowser>




ShowBiolex::ShowBiolex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowBiolex)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif


}

ShowBiolex::~ShowBiolex()
{
    delete ui;
}

void ShowBiolex::on_pushButton_clicked() // read tomato wiki
{

    QString tomatText;
    tomatText = "The tomato is the edible, often red fruit/berry of the nightshade Solanum lycopersicum,[1][2] commonly known as a tomato plant. The species originated in the South American Andes[2] and its use as a food originated in Mexico, and spread throughout the world following the Spanish colonization of the Americas. Its many varieties are now widely grown, sometimes in greenhouses in cooler climates.";



    ui->textBrowser->setText(tomatText);



}

void ShowBiolex::on_pushButton_2_clicked()
{
    QString cucumberText;
    cucumberText = "Cucumber (Cucumis sativus) is a widely cultivated plant in the gourd family Cucurbitaceae. It is a creeping vine that bears cylindrical fruits that are used as culinary vegetables. There are three main varieties of cucumber: slicing, pickling, and burpless. Within these varieties, several different cultivars have emerged. The cucumber is originally from Southern Asia, but now grows on most continents. Many different varieties are traded on the global market.";


            ui->textBrowser->setText(cucumberText);
}

void ShowBiolex::on_pushButton_3_clicked()
{
    QString grape;
    grape = "A grape is a fruiting berry of the deciduous woody vines of the botanical genus Vitis. Grapes can be eaten raw or they can be used for making wine, jam, juice, jelly, grape seed extract, raisins, vinegar, and grape seed oil. Grapes are a non-climacteric type of fruit, generally occurring in clusters.";
    ui->textBrowser->setText(grape);
}

void ShowBiolex::on_pushButton_4_clicked()
{
    this->close();
}
