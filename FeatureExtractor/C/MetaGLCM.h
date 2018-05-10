//
// Created by simo on 07/05/18.
//

#ifndef FEATURESEXTRACTOR_METAGLCM_H
#define FEATURESEXTRACTOR_METAGLCM_H

struct GLCM
{
	int * elements;
    int distance;
    // Values necessary to identify neighbor pixel
    int shiftX;
    int shiftY;
    // Sub Borders in the windows according to direction
    int borderX;
    int borderY;
    int numberOfPairs;
    int numberOfUniquePairs;
};

struct GLCM initializeMetaGLCM(const int distance, const int shiftX, const int shiftY, const int windowRows, const int windowColumns);
void initializeMetaGLCM(GLCM output, const int distance, const int shiftX, const int shiftY);
void printMetaGlcm(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel);
int compressMultiplicity(int * inputArray, const int length, const int numberOfPairs, const int imgGrayLevel);
int addElements(int * metaGLCM, int * elementsToAdd, int * outputArray, const int initialLength, const int numElements, const int numberOfPairs, const int grayLevel);
void dwarf(int * metaGLCM, int * listElements, int lengthGlcm, int lengthElements);
int codifySummedPairs(const int * metaGLCM, int * outputList, const int elements, const int numberOfPairs, const int maxGrayLevel );
int codifySubtractedPairs(const int * metaGLCM, int * outputList, const int elements, const int numberOfPairs, const int maxGrayLevel );


#endif //FEATURESEXTRACTOR_METAGLCM_H
