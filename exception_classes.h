#ifndef EXCEPTION_CLASSES_H
#define EXCEPTION_CLASSES_H

class NoSign{
public:
	NoSign() = default;
	~NoSign() = default;
};

class FileNotFound{
public:
	FileNotFound() = default;
	~FileNotFound() = default;
};

class NotSrtFile{
public:
	NotSrtFile() = default;
	~NotSrtFile() = default;
};

class FileAlreadyExisits{
public:
	FileAlreadyExisits() = default;
	~FileAlreadyExisits() = default;
};

#endif