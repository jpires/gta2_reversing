#include "File.hpp"

GTA_ARY(1, 0x6739C8, char, 256, gTmpStrBuffer_6739C8, {});
GTA_ARY(1, 0x673AE0, char, 256, gOpenFileName_673AE0, {});

void ForceLink_File() { }

// TODO: Move to another file
EXPORT void CC Debug_assert_4A10B0(DWORD, const char *, DWORD)
{
    NOT_IMPLEMENTED();
}

// TODO: Move to stdlib.cpp
EXPORT void* CC malloc_5E4610(size_t size)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT int CC ftell_5E5780(FILE* file)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int CC fclose_5E5930(FILE *file)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT FILE* CC fopen_5E59E0(const char *a1, const char *a2)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT size_t CC fread_5E5A00(void *a1, size_t a2, size_t a3, FILE *a4)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT void CC free_5E46D0(void *lpMem)
{
    NOT_IMPLEMENTED();
}

EXPORT int CC fseek_5E56E0(FILE *a1, int a2, int a3)
{
    NOT_IMPLEMENTED();
    return 0;
}

// TODO: Move to another file Memory.cpp
EXPORT void* CCSTD Memory_Allocate_4F9760(size_t byteToAlloc)
{
    void* pAllocated = malloc_5E4610(byteToAlloc);
    if (!pAllocated)
    {
        Debug_assert_4A10B0(1029, "C:\\gbh\\coop96release\\Memory.cpp", 44);
    }

    return pAllocated;
}

EXPORT bool CCSTD File_IsDriveCdRom_4A4050(char driveLetter)
{
    sprintf(gTmpStrBuffer_6739C8, "%c:", driveLetter);
    return ::GetDriveTypeA(gTmpStrBuffer_6739C8) == DRIVE_CDROM;
}

EXPORT void CCSTD File_SetName_49DF40(const char *pFileName)
{
    strcpy(gOpenFileName_673AE0, pFileName);
}

EXPORT int CCSTD File_GetSize_4A3FB0(FILE *pFileHandle)
{
    const auto curPos = ftell_5E5780(pFileHandle);
    if (curPos == -1)
    {
        Debug_assert_4A10B0(13, "C:\\gbh\\coop96release\\File.cpp", 56);
    }

    if (fseek_5E56E0(pFileHandle, 0, 2))
    {
        Debug_assert_4A10B0(14, "C:\\gbh\\coop96release\\File.cpp", 58);
    }

    const auto endPos = ftell_5E5780(pFileHandle);
    if (endPos == -1)
    {
        Debug_assert_4A10B0(13, "C:\\gbh\\coop96release\\File.cpp", 60);
    }

    if (fseek_5E56E0(pFileHandle, curPos, 0))
    {
        Debug_assert_4A10B0(14, "C:\\gbh\\coop96release\\File.cpp", 62);
    }
    return endPos;
}

EXPORT size_t CCSTD File_Read_4A4230(void *ptr, size_t size, size_t count, FILE *file)
{
    return fread_5E5A00(ptr, size, count, file);
}

EXPORT void* CCSTD File_ReadIntoNewBuffer_4A4120(const char *pFileName, int *totalFileSize)
{
    File_SetName_49DF40(pFileName);

    FILE* pFileHandle= fopen_5E59E0(pFileName, "rb");
    if (!pFileHandle)
    {
        Debug_assert_4A10B0(16, "C:\\gbh\\coop96release\\File.cpp", 141);
    }

    *totalFileSize = File_GetSize_4A3FB0(pFileHandle);

    if (fclose_5E5930(pFileHandle))
    {
        Debug_assert_4A10B0(17, "C:\\gbh\\coop96release\\File.cpp", 145);
    }

    void* pAllocated = Memory_Allocate_4F9760(*totalFileSize);
    pFileHandle = fopen_5E59E0(pFileName, "rb");
    if (!pFileHandle)
    {
        free_5E46D0(pAllocated);
        Debug_assert_4A10B0(16, "C:\\gbh\\coop96release\\File.cpp", 151);
    }

    if (File_Read_4A4230(pAllocated, *totalFileSize, 1u, pFileHandle) != 1)
    {
        free_5E46D0(pAllocated);
        fclose_5E5930(pFileHandle);
        Debug_assert_4A10B0(15, "C:\\gbh\\coop96release\\File.cpp", 158);
    }

    if (!fclose_5E5930(pFileHandle))
    {
        return pAllocated;
    }

    free_5E46D0(pAllocated);
    Debug_assert_4A10B0(17, "C:\\gbh\\coop96release\\File.cpp", 164);
    return pAllocated;
}
