/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #2, Windows
 *
 * Implementing simple crc method
 */

/* do not use UNICODE */
#undef _UNICODE
#undef UNICODE

#include <windows.h>
#include <stdio.h>

#include <utils.h>
#include <crc32.h>

#define BUFSIZE 512
#define CHUNKSIZE 32

static void GenerateCrc(CHAR *sourceFile, CHAR *destFile)
{
	HANDLE hRead, hWrite;
	CHAR buf[BUFSIZE];
	BOOL bRet;
	DWORD bytesRead, bytesWritten;
	int crc = 0;
	int totalWritten = 0;

	/* TODO 1 - Open source file for reading */
		/* open file with name pointed by argv[1] */
	hRead = CreateFile(sourceFile,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

	/* TODO 1 - Create destination file for writing */
		hWrite = CreateFile(destFile,
			GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	printf("here0");

	/* read from file  */
	while (1) {

		ZeroMemory(buf, sizeof(buf));

		/* TODO 1 - Read from source file into buf BUFSIZE bytes */
		bRet = ReadFile(hRead,
						buf,
						BUFSIZE,
						&bytesRead,
						NULL);
		/* TODO 1 - Test for end of file */

		/* calculate crc for buf */
		crc = update_crc(crc, (unsigned char *) buf, bytesRead);

		if(bytesRead <=0)
			break;
	}

	/* TODO 1 - Write crc to destination file */

		bRet = WriteFile(hWrite,
					&crc,
					sizeof(int),
					&bytesWritten,
					NULL);
			DIE(bRet == FALSE, "WriteFile");
			totalWritten += bytesWritten;
	
	printf("here2");

	/* TODO 1 - Close files */
		CloseHandle(hRead);
		CloseHandle(hWrite);

}


static DWORD GetSize(HANDLE file)
{
	DWORD dwSize;
	int currentPos;
	/* TODO 2 - Calculate and return file size using SetFilePointer */
	/* Example: How to get current position */
	

		dwSize = SetFilePointer( 
               file,
               0,           /* offset 0 */
               NULL,        /* no 64bytes offset */
               FILE_END );


		SetFilePointer( 
               file,
               0,           /* offset 0 */
               NULL,        /* no 64bytes offset */
               FILE_BEGIN );
	printf("\n size is %d\n", dwSize);
	return dwSize;
}

static BOOL CompareFiles(CHAR *file1, CHAR *file2)
{
	DWORD  bytesRead=0, bytesRead2=0;
	HANDLE hFile1, hFile2;
	CHAR chunk1[CHUNKSIZE], chunk2[CHUNKSIZE];
	BOOL result = TRUE, bRet;

	/* TODO 3 - Open file handles */
	hFile1 = CreateFile(file1,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

	hFile2 = CreateFile(file2,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

	/* TODO 3 - Compare file size */
	result = (GetSize(hFile1) == GetSize(hFile2));
	/* TODO 3 - Compare the CRC files, chunk by chunk */
	
	  while (1) {
	 	ZeroMemory(chunk1, sizeof(chunk1));
	 	ZeroMemory(chunk2, sizeof(chunk2));
	
		bRet = ReadFile(hFile1,
						chunk1,
						CHUNKSIZE,
						&bytesRead,
						NULL);

	
		bRet = ReadFile(hFile2,
						chunk2,
						CHUNKSIZE,
						&bytesRead2,
						NULL);
	
	  
		if(memcmp(chunk1, chunk2, CHUNKSIZE) != 0){
			result = FALSE;
			break;
		}

		if (bytesRead == 0)
			break;

	  }
	 

exit:
	/* TODO 3 - Close files */
	bRet = CloseHandle(hFile2);
	bRet = CloseHandle(hFile1);


	return result;
}

int main(int argc, char *argv[])
{
	BOOL equal;

	if (argc != 4) {
		fprintf(stderr, "Usage:\n"
				"\tcrc.exe -g <input_file> <output_file> - generate crc\n"
				"\tcrc.exe -c <file1> <file2>            - compare files\n");
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "-g") == 0)
		GenerateCrc(argv[2], argv[3]);

	if (strcmp(argv[1], "-c") == 0) {
		equal = CompareFiles(argv[2], argv[3]);

		if (equal)
			printf("Files are equal\n");
		else
			printf("Files differ\n");
	}

	return 0;
}
