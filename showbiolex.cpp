#include "showbiolex.h"
#include "ui_showbiolex.h"
#include <QDebug>
#include <QTextBrowser>

//TODO: better names
//TODO: set status til true og adjust text naa plant changed
//TODO: add recommendation to other plant

ShowBiolex::ShowBiolex(QWidget *parent) : QDialog(parent),
    ui(new Ui::ShowBiolex)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif

    status = true;
    plantSwitch = 0;
    ui->recbutton->adjustSize();
}

ShowBiolex::~ShowBiolex()
{
    delete ui;
}
// you should be able to apply recommended settings for each plant with a click
void ShowBiolex::on_pushButton_clicked() // read tomato wiki
{
    plantSwitch = 1;
    QString tomatText;
    tomatText = "The tomato is the edible, often red fruit/berry of the nightshade Solanum lycopersicum,[1][2] commonly known as a tomato plant. The species originated in the South American Andes[2] and its use as a food originated in Mexico, and spread throughout the world following the Spanish colonization of the Americas. Its many varieties are now widely grown, sometimes in greenhouses in cooler climates.";
    ui->recbutton->setText("Recommendations");
    ui->recbutton->adjustSize();
    status = true;


    ui->textBrowser->setText(tomatText);



}

void ShowBiolex::init(std::vector<CurrentData *> * ptr){
    ptr_currentDataVector = ptr;
    for(unsigned int i = 0; i < ptr_currentDataVector->size(); i++){
        ui->deviceComboBox->addItem(ptr_currentDataVector->at(i)->getDeviceName());
    }
    ptr_currentData = ptr_currentDataVector->at(0);
}

void ShowBiolex::on_pushButton_2_clicked()
{
    plantSwitch = 2;
    QString cucumberText;
    cucumberText = "Cucumber (Cucumis sativus) is a widely cultivated plant in the gourd family Cucurbitaceae. It is a creeping vine that bears cylindrical fruits that are used as culinary vegetables. There are three main varieties of cucumber: slicing, pickling, and burpless. Within these varieties, several different cultivars have emerged. The cucumber is originally from Southern Asia, but now grows on most continents. Many different varieties are traded on the global market.";


            ui->textBrowser->setText(cucumberText);
}

void ShowBiolex::on_pushButton_3_clicked()
{
    plantSwitch = 3;
    QString grape;
    grape = "A grape is a fruiting berry of the deciduous woody vines of the botanical genus Vitis. Grapes can be eaten raw or they can be used for making wine, jam, juice, jelly, grape seed extract, raisins, vinegar, and grape seed oil. Grapes are a non-climacteric type of fruit, generally occurring in clusters.";
    ui->textBrowser->setText(grape);
}

void ShowBiolex::on_pushButton_4_clicked()
{
    this->close();
}

void ShowBiolex::on_recbutton_clicked()
{
    // create a list of recommendations for the values and set them to the changeAuto settings.
    recommendationsTomato = "Recommendations for tomato: humidity: 20 %, min: 20 c, max 30 c";



    qDebug() << "plant switch: " << plantSwitch;
    if(status){
        switch(plantSwitch)// switchcase with the different events
        {
            case 1:{ //tomato
                ui->textBrowser->setText(recommendationsTomato);
                ui->recbutton->setText("Apply Recommendations");
                ui->recbutton->adjustSize();
                break;
            }
            case 2: //cucumber

            break;

            case 3: // grape

            break;
        default:
            return;

        }
        status = false;

    }
    else{
        switch(plantSwitch)// switchcase with the different events
        {
            case 1:{ //tomato
                ui->recbutton->setText("Recommendations");
                ui->recbutton->adjustSize();
                ptr_currentData->setTargetHumidity(20);
                ptr_currentData->setMinTemp(20);
                ptr_currentData->setMaxTemp(30);
                ui->textBrowser->setText("Tomato setting applied");
                status = true;
                break;
            }
            case 2: //cucumber

            break;

            case 3: // grape

            break;
        default:
            return;

        }
    }
}

void ShowBiolex::on_deviceComboBox_currentIndexChanged(int index)
{
    ptr_currentData = ptr_currentDataVector->at(index);
}
