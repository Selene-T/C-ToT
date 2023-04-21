#include "rpm.hpp"

RPM::RPM(){
	//Constructor For Class, Do Not Remove!
}

RPM::~RPM(){
	//De-Constructor
	//Clean Up! (Close Handle - Not Needed Anymore)
	//CloseHandle(hProcess);
}

bool RPM::Process(char* ProcessName) {

	//Variables
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); //Snapshot To View All Active Processes
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry); //Declare Structure Size And Populate It

	//Loop Through All Running Processes To Find Process
	do
		if (!strcmp(ProcEntry.szExeFile, ProcessName))
		{
			//Store Process ID
			dwPID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);

			//Give Our Handle All Access Rights 
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
			return true;
		}
	while (Process32Next(hPID, &ProcEntry));
	return false;
}