#include "control.h"

control::control()
{

}

void control::init(logfile * ptr_log, CurrentData * ptr_data){
    ptr_logfile = ptr_log;
    ptr_currentdata = ptr_data;
    ptr_connection = new connection;
}

void control::checkvalues(){
    ptr_logfile->setlogevent("*test* checking values *test*");


}
