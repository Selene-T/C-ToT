#ifndef PROCMEM_H //If Not Defined
#define PROCMEM_H //Define Now

#define WIN32_LEAN_AND_MEAN //Excludes Headers We Wont Use (Increase Compile Time)

#include <assert.h>
#include <windows.h> //Standard Windows Functions/Data Types
#include <iostream> //Constains Input/Output Functions (cin/cout etc..)
#include <TlHelp32.h> //Contains Read/Write Functions
#include <string> //Support For Strings
#include <sstream> //Supports Data Conversion

using namespace std;

extern unsigned long base;

class RPM {
protected:

	//STORAGE
	HANDLE hProcess;
	unsigned long dwPID, dwProtection, dwCaveAddress;

	//MISC
	BOOL bPOn, bIOn, bProt;

public:

	//MISC FUNCTIONS
	RPM();
	~RPM();
	int chSizeOfArray(char* chArray); //Return Size Of External Char Array
	int iSizeOfArray(int* iArray); //Return Size Of External Int Array
	bool iFind(int* iAry, int iVal); //Return Boolean Value To Find A Value Inside An Int Array

#pragma region TEMPLATE MEMORY FUNCTIONS

	//REMOVE READ/WRITE PROTECTION
	template <class cData>
	void Protection(unsigned long dwAddress)
	{
		if (!bProt)
			VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(cData), PAGE_EXECUTE_READWRITE, &dwProtection); //Remove Read/Write Protection By Giving It New Permissions
		else
			VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(cData), dwProtection, &dwProtection); //Restore The Old Permissions After You Have Red The dwAddress

		bProt = !bProt;
	}

	//READ MEMORY 
	template <class cData>
	cData Read(unsigned long dwAddress)
	{
		dwAddress += base;
		// Endian Flip for SHORT (16bit) reads
		if (sizeof(cData) == sizeof(SHORT)) { (dwAddress % 4 == 0) ? dwAddress += 2 : dwAddress -= 2; }

		cData cRead; //Generic Variable To Store Data
		ReadProcessMemory(hProcess, (LPVOID)dwAddress, &cRead, sizeof(cData), NULL); //Win API - Reads Data At Specified Location 
		return cRead; //Returns Value At Specified dwAddress
	}

	//READ MEMORY - Pointer
	template <class cData>
	cData Read(unsigned long dwAddress, char* Offset, BOOL Type)
	{
		//Variables
		int iSize = iSizeOfArray(Offset) - 1; //Size Of *Array Of Offsets 
		dwAddress = Read<unsigned long>(dwAddress); //HEX VAL

		//Loop Through Each Offset & Store Hex Value (Address)
		for (int i = 0; i < iSize; i++)
			dwAddress = Read<unsigned long>(dwAddress + Offset[i]);

		if (!Type)
			return dwAddress + Offset[iSize]; //FALSE - Return Address
		else
			return Read<cData>(dwAddress + Offset[iSize]); //TRUE - Return Value
	}

	// MEMORY FUNCTION PROTOTYPES
	virtual bool Process(char* ProcessName); // Return Handle To The Process

#pragma endregion	

};
#endif