#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "fileHelper.h"
#include <stdarg.h>
#include "myMacros.h"




static const char* sortOptStr[eNofSortOpt] = {
	"None","Hour", "Date", "Airport takeoff code", "Airport landing code" };


int	initCompanyFromFile(Company* pComp, AirportManager* pManaer, const char* fileName)
{
	L_init(&pComp->flighDateList);
	if (loadCompanyFromFile(pComp, pManaer, fileName))
	{
		initDateList(pComp);
		return 1;
	}
	return 0;
}

void	initCompany(Company* pComp,AirportManager* pManaer)
{
	printf("-----------  Init Airline Company\n");
	L_init(&pComp->flighDateList);
	
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
}

void	initDateList(Company* pComp)
{	
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if(isUniqueDate(pComp,i))
		{
			char* sDate = createDateString(&pComp->flightArr[i]->date);
			L_insert(&(pComp->flighDateList.head), sDate);
		}
	}
}

int		isUniqueDate(const Company* pComp, int index)
{
	Date* pCheck = &pComp->flightArr[index]->date;
	for (int i = 0; i < index; i++)
	{
		if (equalDate(&pComp->flightArr[i]->date,pCheck))
			return 0;
	}
	return 1;
}

int		addFlight(Company* pComp, const AirportManager* pManager)
{
	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	CHECK_RETURN_0(pComp->flightArr);
	//if (!pComp->flightArr)
		//return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	CHECK_RETURN_0(pComp->flightArr[pComp->flightCount]);
	//if (!pComp->flightArr[pComp->flightCount])
	//	return 0;
	initFlight(pComp->flightArr[pComp->flightCount], pManager);
	if (isUniqueDate(pComp, pComp->flightCount))
	{
		char* sDate = createDateString(&pComp->flightArr[pComp->flightCount]->date);
		L_insert(&(pComp->flighDateList.head), sDate);
	}
	pComp->flightCount++;
	return 1;
}

void	printCompany(const Company* pComp , const char* strName)
{
	printf("Company %s", pComp->name);
	printf("%s:\n", strName);
	printf("Has %d flights\n", pComp->flightCount);
#ifdef DETAIL_PRINT
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), printFlightV);
	printf("\nFlight Date List:");
	L_print(&pComp->flighDateList, printStr);
#endif 
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}

int		saveCompanyToFile(const Company* pComp, const char* fileName)
{
#ifdef BIT_FILE

	if (!saveCompanyToBinaryFile(pComp, fileName))
		return 0;


#else
	FILE* fp;
	fp = fopen(fileName, "wb");

	CHECK_MSG_RETURN_0(fp, "Error open copmpany file to write\n");
	/*if (!fp) {
		printf("Error open copmpany file to write\n");
		return 0;
	}*/
	if (!writeStringToFile(pComp->name, fp, "Error write comapny name\n"))
		return 0;

	if (!writeIntToFile(pComp->flightCount, fp, "Error write flight count\n"))
		return 0;

	if (!writeIntToFile((int)pComp->sortOpt, fp, "Error write sort option\n"))
		return 0;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!saveFlightToFile(pComp->flightArr[i], fp))
			return 0;
	}

	fclose(fp);
#endif
	return 1;
}

int loadCompanyFromFile(Company* pComp, const AirportManager* pManager, const char* fileName)
{
#ifdef BIT_FILE

	if (!loadCompanyFromBinaryFile(pComp, pManager, fileName))
		return 0;

#else
	FILE* fp;
	fp = fopen(fileName, "rb");

	CHECK_MSG_RETURN_0(fp, "Error open company file\n");
	/*if (!fp)
	{
		printf("Error open company file\n");
		return 0;
	}*/
	pComp->flightArr = NULL;

	pComp->name = readStringFromFile(fp, "Error reading company name\n");
	CHECK_RETURN_0(pComp->name);
	//if (!pComp->name)
	//	return 0;
	if (!readIntFromFile(&pComp->flightCount, fp, "Error reading flight count name\n"))
		return 0;
	int opt;
	if (!readIntFromFile(&opt, fp,"Error reading sort option\n"))
		return 0;

	pComp->sortOpt = (eSortOption)opt;

	if (pComp->flightCount > 0)
	{
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));

		CHECK_NULL__MSG_CLOSE_FILE(fp, pComp->flightArr, "Alocation error\n");
		/*if (!pComp->flightArr)
		{
			printf("Alocation error\n");
			fclose(fp);
			return 0;
		}*/
	}
	else
		pComp->flightArr = NULL;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		if (!pComp->flightArr[i])
		{
			printf("Alocation error\n");
			fclose(fp);
			return 0;
		}
		if (!loadFlightFromFile(pComp->flightArr[i], pManager, fp))
			return 0;
	}

	fclose(fp);
#endif
	return 1;
}

void	sortFlight(Company* pComp)
{
	pComp->sortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pComp->sortOpt)
	{
	case eHour:
		compare = compareByHour;
		break;
	case eDate:
		compare = compareByDate;
		break;
	case eSorceCode:
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		compare = compareByCodeDest;
		break;
	
	}

	if (compare != NULL)
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);

}

void	findFlight(const Company* pComp)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Flight f = { 0 };
	Flight* pFlight = &f;


	switch (pComp->sortOpt)
	{
	case eHour:
		f.hour = getFlightHour();
		compare = compareByHour;
		break;
	case eDate:
		getchar();
		getCorrectDate(&f.date);
		compare = compareByDate;
		break;
	case eSorceCode:
		getchar();
		getAirportCode(f.originCode);
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		getchar();
		getAirportCode(f.destCode);
		compare = compareByCodeDest;
		break;
	}

	if (compare != NULL)
	{
		Flight** pF = bsearch(&pFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);
		if (pF == NULL)
			printf("Flight was not found\n");
		else {
			printf("Flight found, ");
			printFlight(*pF);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}

}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >eNofSortOpt);

	return (eSortOption)opt;
}

void	freeCompany(Company* pComp)
{
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), freeFlight);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->flighDateList, freePtr);
}

char* combiningStrings(const char* str, ...)
{
	va_list list;
	const char* strTemp;
	char* longStr = NULL;
	int combineLength = 0;
	int len;

	va_start(list, str);
	strTemp = str;
	while (strTemp != NULL)
	{
		len = (int)strlen(strTemp);
		longStr = (char*)realloc(longStr, (combineLength + len + 2) * sizeof(char));
		CHECK_RETURN_NULL(longStr);
		//if (!longStr)
		//	return NULL;

		if (combineLength == 0)
		{
			strcpy(longStr, "_");
			strcat(longStr, strTemp);
			combineLength = len + 1;
		}
		else {
			strcat(longStr, "_");
			strcat(longStr, strTemp);
			combineLength += len +1;
		}
		strTemp = va_arg(list, const char*);
	}

	va_end(list);
	return longStr;
}

int loadCompanyFromBinaryFile(Company* pComp, const AirportManager* pManager, const char* fileName)
{
	BYTE data[2] = { 0 };
	FILE* fp;
	int nameLen;
	fp = fopen(fileName, "rb");
	CHECK_MSG_RETURN_0(fp, "Error open company file\n");
	//if (!fp)
	//{
	//	printf("Error open company file\n");
	//	return 0;
	//}
	pComp->flightArr = NULL;

	if (fread(data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	pComp->flightCount = (int)(data[1] << 1 | data[0] >> 7);
	if (pComp->flightCount > 0)
	{
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * (sizeof(Flight*)));
		if (!(pComp->flightArr))
		{
			fclose(fp);
			return 0;
		}
	}
	
	pComp->sortOpt =(int) (data[0] >> 4 & 0x07);

	nameLen = (int)(data[0] & 0x0F);
	pComp->name = (char*)malloc((nameLen + 1) * sizeof(char));
	if (!pComp->name)
	{	
		fclose(fp);
		return 0;
	}

	if (fread(pComp->name, sizeof(char), nameLen + 1, fp) != (nameLen + 1))
	{
		fclose(fp);
		return 0;
	}
	
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!readFlightFromBinaryFile(pComp, pManager, fp, i))
		{
			fclose(fp);
			return 0;
		}
	}

	return 1;
}


int readFlightFromBinaryFile(Company* pComp, const AirportManager* pManager, FILE* fp , int index)
{
	char codeDes[CODE_LENGTH + 1] = { 0 };
	char codeSrc[CODE_LENGTH + 1] = { 0 };

	Flight* pFlight = (Flight*)malloc(sizeof(Flight));
	if(!pFlight)
		return 0;
	if (fread(codeSrc, sizeof(char), CODE_LENGTH, fp) != CODE_LENGTH)
		return 0;
	if(fread(codeDes, sizeof(char), CODE_LENGTH, fp) != CODE_LENGTH)
		return 0;

	codeDes[CODE_LENGTH] = '\0';
	codeSrc[CODE_LENGTH] = '\0';
	if(!findAirportByCode(pManager , codeDes) || !findAirportByCode(pManager, codeSrc))
		return 0;

	strcpy(pFlight->originCode, codeSrc);
	strcpy(pFlight->destCode, codeDes);

	BYTE data[4] = { 0 };
	if (fread(data, sizeof(BYTE), 4, fp) != 4)
		return 0;
	pFlight->date.year = (int)(data[3] << 10 | data[2] << 2 | data[1] >> 6);
	pFlight->date.month = (int)((data[1] >> 2) & 0x0F);
	pFlight->date.day = (int)((data[1] & 0x03) << 3 | data[0] >> 5);
	pFlight->hour = (int)(data[0] & 0x1F);
	
	pComp->flightArr[index] = pFlight;
	return 1;
}



int saveCompanyToBinaryFile(const Company* pComp, const char* fileName)
{
	BYTE data[2] = { 0 };
	FILE* fp;
	fp = fopen(fileName, "wb");
	CHECK_MSG_RETURN_0(fp, "Error open company file\n");
	//if (!fp)
	//{
	//	printf("Error open company file\n");
	//	return 0;
	//}
	BYTE nameLen = (BYTE)(strlen(pComp->name));
	data[1] |= pComp->flightCount >> 1;
	data[0] = (((pComp->flightCount & 0x01) << 7) | pComp->sortOpt << 4) | nameLen;
	
	if (fwrite(data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	if (fwrite(pComp->name, sizeof(char), nameLen + 1, fp) != (nameLen + 1))
	{
		fclose(fp);
		return 0;
	}

	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!writeFlightFromBinaryFile(pComp->flightArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}



	return 1;

}

int writeFlightFromBinaryFile(const Flight* pFlight, FILE* fp)
{
	if(fwrite(pFlight->originCode , sizeof(char) , CODE_LENGTH, fp) != CODE_LENGTH)
		return 0;
	if (fwrite(pFlight->destCode, sizeof(char), CODE_LENGTH, fp) != CODE_LENGTH)
		return 0;
	BYTE data[4] = { 0 };
	
	data[3] = (pFlight->date.year >> 10);
	data[2] = (pFlight->date.year >> 2);
	data[1] = (pFlight->date.year & 0x03) << 6 | pFlight->date.month << 2 | pFlight->date.day >> 3;
	data[0] = pFlight->date.day << 5 | pFlight->hour;

	if (fwrite(data, sizeof(BYTE), 4, fp) != 4)
		return 0;
	return 1;

}