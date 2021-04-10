#include <iostream>
#include <iostream>
//#include <iomanip>>
#include <fstream>
#include <sstream>
#include <thread>
#include <exception>
#include <future>
#include <chrono>
#include <vector>

#include "exception_classes.h"
#include "helper_functions.h"

using namespace std::chrono_literals;

/**
 * Prints the initial dialog to the user on the console to get file path.
 *
 * @return file path string.
 */
 
std::string GetFilePath(){
	std::string Path;
	std::cout << "Procced by entering the path of the srt file you want to shift."
	<< std::endl << std::endl;
	std::getline (std::cin,Path);
	return Path;
}
 
double StrToFloat(const std::string & num_str){
    std::string::size_type sz; 
    double num;
	num = std::stof(num_str, &sz); 
	return num;
}

 /**
 * Gets time shift from user.
 *
 * @return time shift double.
 */
 
double GetTimeShift(){
	double TimeShift;
	std::string TimeShift_str;
	std::cout << "Enter the time shift you want to apply on the subtitles." << std::endl;
	std::cout << "Please, take caution that timeshift should be entered as '+' or '-' followed by shift seconds." << std::endl;
	std::cout << "For example, for delaying subtitles by 1.5 seconds, I'd enter '+1.5'"
	<< std::endl<<std::endl;
	std::getline (std::cin,TimeShift_str);
	if(TimeShift_str[0] != '+' && TimeShift_str[0] != '-'){
		throw NoSign();
	}
	
	try{
		TimeShift = StrToFloat(TimeShift_str);
	}
	
	catch(...){
		std::cerr << "You didn't enter a float"<<std::endl <<"Terminating"<<std::endl;
		std::terminate();
	}
	return TimeShift;
}

 /**
 * Prints new lines with special characters in between
 * to distinguish between different sections of the program.
 */
 
void EndSection(){
	
	std::cout<< std::endl
	<< "---------------------------------------------------------------------" <<
	std::endl << std::endl;
}

/**
 * Manages the processing animation until
 * processing is done.
 */
 
void PrintProcessing(std::future<void> && fut){
	while(fut.wait_for(0ms) != std::future_status::ready){
		std::cout<<"\r             "<<std::flush;
		std::cout<<"\rProcessing"<<std::flush;
		std::this_thread::sleep_for(300ms);
		std::cout<<"\rProcessing."<<std::flush;
		std::this_thread::sleep_for(300ms);
		std::cout<<"\rProcessing.."<<std::flush;
		std::this_thread::sleep_for(300ms);
		std::cout<<"\rProcessing..."<<std::flush;
		std::this_thread::sleep_for(300ms);
	}
	std::cout<<std::endl;
	EndSection();
	std::cout<<std::endl<<"Finished processing"<<std::endl;
}





/**
 * Allocates another file and writes a
 * shifted version of the old file.
 * 
 * @param Fpath string which points to the file.
 * @param TS double timeshift.
 */
void Process(std::string Fpath, double TS){
	std::this_thread::sleep_for(2s);
	std::string NewFilePath;
	try{
		NewFilePath = helper::GetNewFilePath(Fpath);
	}
	catch(const FileAlreadyExisits& ex){
		std::cerr << "File already exists."<<std::endl;
		std::terminate();
	}	
	std::vector<int> Shifts = helper::ProcessShift(TS);
	
	std::ifstream IFile{Fpath};
	std::ofstream OFile{NewFilePath};
	std::string Line;
	std::vector<int> FailedLines;
	
	int i = 0;
	while (std::getline(IFile, Line)){
		i++;
		if(Line.find("-->") != std::string::npos){
			try{
				Line = helper::ApplyShiftToLine(Line, Shifts);
			}
			catch(...){
				FailedLines.push_back(i);
			}
			}
		// Write Line to the newly created file.
		OFile << Line << '\n';
		}
	IFile.close();
	OFile.close();
	
	for(int ID: FailedLines){
		std::cout<<"\nLine Number "<<ID<<" failed\n";
	}
	}



int main()
{
	std::string FilePath = GetFilePath();	// Getting file path.
	double TimeShift;
	// Try to open file.
	{
		std::ifstream i_file(FilePath,std::ios::in);
		std::string Extension = FilePath.substr(FilePath.length() - 4,4);
		try{
			if (!(i_file)){
				throw FileNotFound();
			}
			else if(Extension != ".srt") {
				throw NotSrtFile();
				}
		}
		catch(const FileNotFound& ex){
			std::cerr << "File Not found." <<std::endl<<
			"Terminating."<<std::endl;
			std::terminate();
			}
		catch(const NotSrtFile& ex){
			std::cerr << "That's not an srt file." <<std::endl<<
			"Terminating."<<std::endl;
			std::terminate();
			}
			i_file.close();
	}
		EndSection();
	// Getting time shift from user.
	try{
		TimeShift = GetTimeShift();
	}
	catch(const NoSign & ex){
		std::cerr << "You didn't enter a sign"<<std::endl <<"Program terminated."<<std::endl;
		std::terminate();
	}
	EndSection();
	
	// Start processing.
	
	std::future<void> fut = std::async(std::launch::async,Process,
	FilePath,TimeShift);
	PrintProcessing(std::move(fut));
	
	return 0;
}
