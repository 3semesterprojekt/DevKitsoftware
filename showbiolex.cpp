#include "showbiolex.h"
#include "ui_showbiolex.h"
#include <QDebug>
#include <QTextBrowser>



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


void ShowBiolex::init(std::vector<CurrentData *> * ptr, Database* ptr2){

    QStringList plants;
    plants << "Tomato" << "Cucumber" << "Grape" << "Basil" << "Strawberry";

    ptr_currentDataVector = ptr;
    for(unsigned int i = 0; i < ptr_currentDataVector->size(); i++){
        ui->deviceComboBox->addItem(ptr_currentDataVector->at(i)->getDeviceName());
    }

    for(int i = 0; i < plants.size(); i++){
        ui->plantCombo->addItem(plants.at(i));
    }

    ptr_currentData = ptr_currentDataVector->at(0);
    ptr_database = ptr2;
}


void ShowBiolex::on_ReturnButton_clicked()
{
    ptr_database->WriteAutoConfigRow(ptr_currentDataVector);
    this->close();
}

void ShowBiolex::setHumMinMaxTemp(int hum, int minTemp, int maxTemp)
{

    ptr_currentData->setTargetHumidity(hum);
    ptr_currentData->setMinTemp(minTemp);
    ptr_currentData->setMaxTemp(maxTemp);



}

void ShowBiolex::on_recbutton_clicked() // find good recommendations for all 3 plants
{

    // create a list of recommendations for the values and set them to the changeAuto settings.
    recommendationsTomato = "Recommendations for tomato: humidity: 20 %, min: 20 c, max 30 c";
    recommendationsCucumber = "Recommendations for cucumber: humidity: 30 %, min: 20 c, max 30 c";
    recommendationsGrape = "Recommendations for grape: humidity: 30 %, min: 20 c, max 30 c";
    recommendationsBasil = "Recommendations for basil: humidity: 25 %, min: 20 c, max 30 c";
    recommendationsStrawBerry = "Recommendations for strawberry: humidity: 22 %, min: 20 c, max 30 c";
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
            ui->textBrowser->setText(recommendationsCucumber);
            ui->recbutton->setText("Apply Recommendations");
            ui->recbutton->adjustSize();
            break;

            case 3: // grape
            ui->textBrowser->setText(recommendationsGrape);
            ui->recbutton->setText("Apply Recommendations");
            ui->recbutton->adjustSize();
            break;

           case 4: // basil
            ui->textBrowser->setText(recommendationsBasil);
            ui->recbutton->setText("Apply Recommendations");
            ui->recbutton->adjustSize();
            break;

           case 5: // strawberry
            ui->textBrowser->setText(recommendationsStrawBerry);
            ui->recbutton->setText("Apply Recommendations");
            ui->recbutton->adjustSize();
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
                setHumMinMaxTemp(20,20,30);
                ui->textBrowser->setText("Tomato settings applied");
                status = true;
                break;
            }
            case 2: //cucumber
            ui->recbutton->setText("Recommendations");
            ui->recbutton->adjustSize();
            setHumMinMaxTemp(30,20,30);
            ui->textBrowser->setText("Cucumber settings applied");
            status = true;
            break;

            case 3: // grape
            ui->recbutton->setText("Recommendations");
            ui->recbutton->adjustSize();
            setHumMinMaxTemp(30,20,30);
            ui->textBrowser->setText("Grape settings applied");
            status = true;
            break;

            case 4: // basil
            ui->recbutton->setText("Recommendations");
            ui->recbutton->adjustSize();
            setHumMinMaxTemp(25,20,30);
            ui->textBrowser->setText("Basil settings applied");
            status = true;
            break;

            case 5: // strawberry
            ui->recbutton->setText("Recommendations");
            ui->recbutton->adjustSize();
            setHumMinMaxTemp(22,20,30);
            ui->textBrowser->setText("Strawberry settings applied");
            status = true;
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









void ShowBiolex::on_plantCombo_currentIndexChanged(int index)
{

    switch(index){
    case 0:
    {
        qDebug() << "Index 0 activated";
        status = true;
        plantSwitch = 1;
        QString tomatText;
        tomatText = "The tomato is the edible, often red fruit/berry of the nightshade Solanum lycopersicum, commonly known as a tomato plant. The species originated in the South American Andes and its use as a food originated in Mexico, and spread throughout the world following the Spanish colonization of the Americas. Its many varieties are now widely grown, sometimes in greenhouses in cooler climates.\n Source: Wikipedia";
        ui->recbutton->setText("Recommendations");
        ui->recbutton->adjustSize();
        status = true;
        ui->textBrowser->setText(tomatText);

        qDebug() << "Case 0 done";
        break;
    }
    case 1:
    {
        status = true;
        plantSwitch = 2;
        QString cucumberText;
        cucumberText = "Cucumber (Cucumis sativus) is a widely cultivated plant in the gourd family Cucurbitaceae. It is a creeping vine that bears cylindrical fruits that are used as culinary vegetables. There are three main varieties of cucumber: slicing, pickling, and burpless. Within these varieties, several different cultivars have emerged. The cucumber is originally from Southern Asia, but now grows on most continents. Many different varieties are traded on the global market.\n Source: Wikipedia";
        ui->textBrowser->setText(cucumberText);
    }
        break;
    case 2:
    {
        status = true;
        plantSwitch = 3;
        QString grape;
        grape = "A grape is a fruiting berry of the deciduous woody vines of the botanical genus Vitis. Grapes can be eaten raw or they can be used for making wine, jam, juice, jelly, grape seed extract, raisins, vinegar, and grape seed oil. Grapes are a non-climacteric type of fruit, generally occurring in clusters.\n Source: Wikipedia";
        ui->textBrowser->setText(grape);

    }
        break;
    case 3:
    {
        status = true;
        plantSwitch = 4;
        QString basil;
        basil = "Basil, Thai basil, or sweet basil, is a common name for the culinary herb Ocimum basilicum of the family Lamiaceae (mints), sometimes known as Saint Joseph's Wort in some English-speaking countries. Basil is native to India, China, Southeast Asia, and New Guinea. It was originally domesticated in India, having been cultivated there for more than 5,000 years, but was thoroughly familiar to Theophrastus and Dioscorides. It is a half-hardy annual plant, best known as a culinary herb prominently featured in Italian cuisine, and also plays a major role in Southeast Asian cuisines of Indonesia, Thailand, Vietnam, Cambodia, Laos, and the cuisine of Taiwan. Depending on the species and cultivar, the leaves may taste somewhat like anise, with a strong, pungent, often sweet smell.\n Source: Wikipedia";
        ui->textBrowser->setText(basil);

    }
        break;
    case 4:
    {
        status = true;
        plantSwitch = 5;
        QString strawBerry;
        strawBerry = "The garden strawberry (or simply strawberry (Fragaria × ananassa) is a widely grown hybrid species of the genus Fragaria (collectively known as the strawberries). It is cultivated worldwide for its fruit. The fruit (which is not a botanical berry, but an aggregate accessory fruit) is widely appreciated for its characteristic aroma, bright red color, juicy texture, and sweetness. It is consumed in large quantities, either fresh or in such prepared foods as preserves, fruit juice, pies, ice creams, milkshakes, and chocolates. Artificial strawberry flavoring is also widely used in many products like hand sanitizers, lip gloss, perfume, and many others.\n Source: Wikipedia";
        ui->textBrowser->setText(strawBerry);
    }
    break;
    default:
        return;
    }
}
