#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
#include "GeneralList.h"

//#define BIT_FILE
#define DETAIL_PRINT

typedef enum { eNone, eHour, eDate,eSorceCode,eDestCode, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];


typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	eSortOption	sortOpt;
	LIST		flighDateList;
}Company;

typedef unsigned char  BYTE;

int		initCompanyFromFile(Company* pComp, AirportManager* pManaer, const char* fileName);
void	initCompany(Company* pComp, AirportManager* pManaer);
void	initDateList(Company* pComp);
int		isUniqueDate(const Company* pComp, int index);
int		addFlight(Company* pComp,const AirportManager* pManager);

char* combiningStrings(const char* str, ...);

void	printCompany(const Company* pComp , const char* str);
void	printFlightsCount(const Company* pComp);

int		saveCompanyToFile(const Company* pComp, const char* fileName);
int		loadCompanyFromFile(Company* pComp, const AirportManager* pManager, const char* fileName);

void	sortFlight(Company* pComp);
void	findFlight(const Company* pComp);
int loadCompanyFromBinaryFile(Company* pComp, const AirportManager* pManager, const char* fileName);
int readFlightFromBinaryFile(Company* pComp, const AirportManager* pManager, FILE* fp, int index);
int saveCompanyToBinaryFile(const Company* pComp, const char* fileName);
int writeFlightFromBinaryFile(const Flight* pFlight, FILE* fp);
eSortOption showSortMenu();

void	freeCompany(Company* pComp);

#endif

