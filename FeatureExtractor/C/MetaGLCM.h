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
    int shiftRows;
    int shiftColumns;
    int windowDimension;
    // Sub Borders in the windows according to direction
    int borderRows;
    int borderColumns;
    int numberOfPairs;
    int numberOfUniquePairs;
    int maxGrayLevel; // Private field, for convenience
};

struct GLCM initializeMetaGLCM(const int distance, const int shiftX, const int shiftY, const int windowDimension, const int grayLevel);
void initializeMetaGLCM(struct GLCM * input, const int distance, const int shiftX, const int shiftY, const int windowDimension, const int grayLevel);
void initializeMetaGLCMElements(struct GLCM * metaGLCM, const int * pixelPairs);

void printGLCMData(const GLCM input);
void printGLCMData(struct GLCM * input);
void printMetaGlcm(const struct GLCM metaGLCM);
void printAggrregatedMetaGlcm(const int * aggregatedList, const int length, const int numberOfUniquePairs);

int compressAggregatedMultiplicity(int * summedPairs, int length, const int numberOfPairs);
// Senza senso ne implementazione
void compressMultiplicity(struct GLCM * metaGLCM);
void addElements(struct GLCM * metaGLCM, int * elementsToAdd, int elementsLength);
void dwarf(int * metaGLCM, int * listElements, int lengthGlcm, int lengthElements);

int codifySummedPairs(const GLCM metaGLCM, int * outputList);
int codifySubtractedPairs(const GLCM metaGLCM, int * outputList);

#endif //FEATURESEXTRACTOR_METAGLCM_H