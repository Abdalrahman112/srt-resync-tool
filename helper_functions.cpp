#include "helper_functions.h"

namespace helper{

static std::string TimeToShiftStr(int HShift, int MinShift,
int SecShift, int FloatShift);
	static int ApplyShift(int Shift, std::string Origin);
}

static std::string helper::TimeToShiftStr(int HShift, int MinShift,
int SecShift, int FloatShift){
	std::string HStr;
	if (HShift >= 10){
		HStr = std::to_string(HShift);
	}
	else{
		HStr = '0' + std::to_string(HShift);
	}
	
	std::string MinStr;
	if (MinShift >= 10){
		MinStr = std::to_string(MinShift);
	}
	else{
		MinStr = '0' + std::to_string(MinShift);
	}
	
	std::string SecStr;
	if (SecShift >= 10){
		SecStr = std::to_string(SecShift);
	}
	else{
		SecStr = '0' + std::to_string(SecShift);
	}
	
	std::string FloatStr;
	
	if(FloatShift< 10){
		FloatStr = "00" + std::to_string((int) (FloatShift));
	}
	else if(FloatShift< 100){
		FloatStr = '0' + std::to_string((int) (FloatShift));
	}
	else{
		FloatStr = std::to_string((int) (FloatShift));
	}
	while(FloatStr.length() < 3){
		FloatStr += '0';
	}
	std::string FormattedShift = HStr+':'+MinStr+':'+SecStr+','+FloatStr;
	
	return FormattedShift;
}

std::vector<int> helper::ProcessShift(double timeshift){
	int 	HShift = timeshift / 3600;
	int  	MinShift= (timeshift - HShift * 3600) / 60;
	int  	SecShift= timeshift - MinShift * 60 - HShift * 3600;
	int 	FloatShift = (timeshift - (int) timeshift) * 1000;
	
	return {HShift, MinShift, SecShift, FloatShift};
	}
	
std::string helper::GetNewFilePath(std::string OriginalFilePath){
	int LastSlash = OriginalFilePath.find_last_of("/\\");
	
	std::string NewFilePath = OriginalFilePath.substr(0,LastSlash+1)
	+ "Resynced" // + date::format("%T", std::chrono::system_clock::now()) +".srt";
	+ '_' +OriginalFilePath.substr(LastSlash+1);
	{
		std::ifstream NewFile{NewFilePath};
		if (NewFile){
			throw FileAlreadyExisits();
		}
		NewFile.close();
	}
	
	return NewFilePath;
}

static int helper::ApplyShift(int Shift, std::string Origin){
	return std::stoi(Origin) + Shift;
}
std::string helper::ApplyShiftToLine(std::string Origin,
		std::vector<int> Shifts){
			int ShiftHour = Shifts[0]; 
			int ShiftMinute = Shifts[1]; 
			int ShiftSeconds = Shifts[2]; 
			int ShiftFloat = Shifts[3]; 
			
			int FirstPos1 = 0;
			int FirstPos2 = 17;
			
			std::string ShiftedStr;
			std::string SubOrigin;
			int HOrigin, MOrigin, SOrigin, FOrigin;
			
			//First time.
			
			SubOrigin = Origin.substr(FirstPos1,2);
			HOrigin = helper::ApplyShift(ShiftHour, SubOrigin);
			
			SubOrigin = Origin.substr(FirstPos1 + 3, 2);
			MOrigin = helper::ApplyShift(ShiftMinute, SubOrigin);
			
			if (MOrigin >= 60){
				HOrigin += 1;
				MOrigin -= 60;
			}
			else if(MOrigin < 0){
				HOrigin -= 1;
				MOrigin += 60;
			}
			
			SubOrigin = Origin.substr(FirstPos1 + 6, 2);
			SOrigin = helper::ApplyShift(ShiftSeconds, SubOrigin);
			
			if (SOrigin >= 60){
				MOrigin += 1;
				SOrigin -= 60;
			}
			else if(SOrigin < 0){
				MOrigin -= 1;
				SOrigin += 60;
			}
			
			SubOrigin = Origin.substr(FirstPos1 + 9, 3);
			FOrigin = helper::ApplyShift(ShiftFloat, SubOrigin);
			
			if (FOrigin >= 1000){
				SOrigin += 1;
				FOrigin -= 1000;
			}
			else if(FOrigin < 0){
				SOrigin -= 1;
				FOrigin += 1000;
			}
			
			ShiftedStr = helper::TimeToShiftStr(HOrigin,MOrigin,SOrigin,FOrigin);
			
			if (ShiftedStr.find('-') != std::string::npos){
				ShiftedStr = "00:00:00,000";
			}
			
			Origin.replace(FirstPos1, 12, ShiftedStr);
			
			// Second time.
			SubOrigin = Origin.substr(FirstPos1,2);
			HOrigin = helper::ApplyShift(ShiftHour, SubOrigin);
			
			SubOrigin = Origin.substr(FirstPos2 + 3, 2);
			MOrigin = helper::ApplyShift(ShiftMinute, SubOrigin);
			
			if (MOrigin >= 60){
				HOrigin += 1;
				MOrigin -= 60;
			}
			else if(MOrigin < 0){
				HOrigin -= 1;
				MOrigin += 60;
			}
			
			SubOrigin = Origin.substr(FirstPos2 + 6, 2);
			SOrigin = helper::ApplyShift(ShiftSeconds, SubOrigin);
			
			if (SOrigin >= 60){
				MOrigin += 1;
				SOrigin -= 60;
			}
			else if(SOrigin < 0){
				MOrigin -= 1;
				SOrigin += 60;
			}
			
			SubOrigin = Origin.substr(FirstPos2 + 9, 3);
			FOrigin = helper::ApplyShift(ShiftFloat, SubOrigin);
			
			if (FOrigin >= 1000){
				SOrigin += 1;
				FOrigin -= 1000;
			}
			else if(FOrigin < 0){
				SOrigin -= 1;
				FOrigin += 1000;
			}
			
			ShiftedStr = helper::TimeToShiftStr(HOrigin,MOrigin,SOrigin,FOrigin);
			
			if (ShiftedStr.find('-') != std::string::npos){
				ShiftedStr = "00:00:00,000";
			}
			Origin.replace(FirstPos2,12 , ShiftedStr);
			
		return Origin;
		}