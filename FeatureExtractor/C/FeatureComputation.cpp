//
// Created by simo on 07/05/18.
//

#include "FeatureComputation.h"
#include "GrayPair.h"

#include <math.h>
#include <iostream>

double computeASM(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double angularSecondMoment = 0;
    GrayPair actualPair;
    double actualPairProbability;
    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;
        angularSecondMoment += pow((actualPairProbability),2);
    }
    return angularSecondMoment;

}

double computeAutocorrelation(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double autocorrelation = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        autocorrelation += actualPair.grayLevelI * actualPair. grayLevelJ * actualPairProbability;
    }
    return autocorrelation;
}


double computeEntropy(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double entropy = 1;
    GrayPair actualPair;
    double actualPairProbability;
    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        entropy += actualPairProbability * log(actualPairProbability);
        // No pairs with 0 probability, so log is safe
    }
    return (-1*entropy);
}

double computeMaximumProbability(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double maxProb;
    GrayPair actualPair = unPack(metaGLCM[0], numberOfPairs, maxGrayLevel);
    double actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;
    maxProb = actualPairProbability;

    for(int i=1 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        if(actualPairProbability > maxProb)
        {
            maxProb = actualPairProbability;
        }
    }
    return maxProb;
}

double computeHomogeneity(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double homogeneity = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        homogeneity += actualPairProbability /
                       (1 + fabs(actualPair.grayLevelI - actualPair.grayLevelJ));

    }
    return homogeneity;
}


double computeContrast(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double contrast = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        contrast += actualPairProbability
                    * (pow(fabs(actualPair.grayLevelI - actualPair.grayLevelJ), 2));

    }
    return contrast;
}

double computeCorrelation(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel, const double muX, const double muY, const double sigmaX, const double sigmaY)
{
    double correlation = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        correlation += ((actualPair.grayLevelI - muX) * (actualPair.grayLevelJ - muY) * actualPairProbability )
                       /(sigmaX * sigmaY);

    }
    return correlation;
}

double computeClusterProminecence(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel, const double muX, const double muY)
{
    double clusterProminecence = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        clusterProminecence += pow ((actualPair.grayLevelI + actualPair.grayLevelJ -muX - muY), 4) * actualPairProbability;
    }
    return clusterProminecence;
}

double computeClusterShade(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel, const double muX, const double muY)
{
    double clusterShade = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        clusterShade += pow ((actualPair.grayLevelI + actualPair.grayLevelJ -muX - muY), 3) * actualPairProbability;
    }
    return clusterShade;
}

double computeSumOfSquares(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel, const double mu)
{
    double sumSquares = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        sumSquares += pow ((actualPair.grayLevelI - mu), 2) * actualPairProbability;
    }
    return sumSquares;
}

double computeInverceDifferentMomentNormalized(const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double inverceDifference = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        inverceDifference += actualPairProbability /
                             ((1+pow((actualPair.grayLevelI - actualPair.grayLevelJ),2))/maxGrayLevel);
    }
    return inverceDifference;
}

// SUM Aggregated features
double computeSumAverage(const int * summedMetaGLCM, const int length, const int numberOfPairs)
{
    double result = 0;
    AggregatedPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = aggregatedPairUnPack(summedMetaGLCM[i], numberOfPairs);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        result += actualPair.aggregatedGrayLevels * actualPairProbability;
    }
    return result;
}

double computeSumEntropy(const int * summedMetaGLCM, const int length, const int numberOfPairs)
{
    double result = 0;
    AggregatedPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = aggregatedPairUnPack(summedMetaGLCM[i], numberOfPairs);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        result += log(actualPair.aggregatedGrayLevels) * actualPairProbability;
    }
    return result;
}

double computeSumVariance(const int * summedMetaGLCM, const int length, const int numberOfPairs, const double sumEntropy)
{
    double result = 0;
    AggregatedPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = aggregatedPairUnPack(summedMetaGLCM[i], numberOfPairs);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        result += pow((actualPair.aggregatedGrayLevels - sumEntropy),2)
                  * actualPairProbability;
    }
    return result;
}

double computeDifferenceEntropy(const int * aggregatedMetaGLCM, const int length, const int numberOfPairs)
{
    double result = 0;
    AggregatedPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = aggregatedPairUnPack(aggregatedMetaGLCM[i], numberOfPairs);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        result += log(actualPairProbability) * actualPairProbability;
    }
    return -1*result;
}

double computeDifferenceVariance(const int * aggregatedMetaGLCM, const int length, const int numberOfPairs)
{
    double result = 0;
    AggregatedPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = aggregatedPairUnPack(aggregatedMetaGLCM[i], numberOfPairs);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        result += (actualPair.aggregatedGrayLevels^2) * actualPairProbability;
    }
    return result;
}


// Mean of all probabilities
double computeMean(const int* metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double mu = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        mu += actualPairProbability;
    }
    return mu;
}

// Mean of
double computeMuX(const int* metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double muX = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        muX += actualPair.grayLevelI * actualPairProbability;
    }
    return muX;
}

double computeMuY(const int* metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    double muY = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        muY += actualPair.grayLevelJ * actualPairProbability;
    }
    return muY;
}

double computeSigmaX(const int* metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel, const double muX)
{
    double sigmaX = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        sigmaX += pow((actualPair.grayLevelI - muX),2) * actualPairProbability;
    }

    return sqrt(sigmaX);
}

double computeSigmaY(const int* metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel, const double muY)
{
    double sigmaY = 0;
    GrayPair actualPair;
    double actualPairProbability;

    for(int i=0 ; i<length; i++)
    {
        actualPair = unPack(metaGLCM[i], numberOfPairs, maxGrayLevel);
        actualPairProbability = ((double) actualPair.multiplicity)/numberOfPairs;

        sigmaY += pow((actualPair.grayLevelJ - muY),2) * actualPairProbability;
    }

    return sqrt(sigmaY);
}


void computeFeatures(double * output, const int * metaGLCM, const int length, const int numberOfPairs, const int maxGrayLevel)
{
    output[0]= computeASM(metaGLCM,length,numberOfPairs,maxGrayLevel);
    output[1]= computeAutocorrelation(metaGLCM,length,numberOfPairs,maxGrayLevel);
    output[2]= computeEntropy(metaGLCM,length,numberOfPairs,maxGrayLevel);
    output[3]= computeMaximumProbability(metaGLCM,length,numberOfPairs,maxGrayLevel);
    output[4]= computeHomogeneity(metaGLCM,length,numberOfPairs,maxGrayLevel);
    output[5]= computeContrast(metaGLCM,length,numberOfPairs,maxGrayLevel);

    double muX, muY, mu, sigmaX, sigmaY;
    mu = computeMean(metaGLCM,length,numberOfPairs,maxGrayLevel);
    muX = computeMuX(metaGLCM,length,numberOfPairs,maxGrayLevel);
    muY = computeMuY(metaGLCM,length,numberOfPairs,maxGrayLevel);
    sigmaX = computeSigmaX(metaGLCM,length,numberOfPairs,maxGrayLevel, muX);
    sigmaY = computeSigmaY(metaGLCM,length,numberOfPairs,maxGrayLevel, muY);

    output[6]= computeCorrelation(metaGLCM,length,numberOfPairs,maxGrayLevel, muX, muY, sigmaX, sigmaY);
    output[7]= computeClusterProminecence(metaGLCM,length,numberOfPairs,maxGrayLevel, muX, muY);
    output[8]= computeClusterShade(metaGLCM,length,numberOfPairs,maxGrayLevel, muX, muY);
    output[9]= computeSumOfSquares(metaGLCM,length,numberOfPairs,maxGrayLevel, mu);
    output[10]= computeInverceDifferentMomentNormalized(metaGLCM,length,numberOfPairs,maxGrayLevel);

    /*
    output[11]= computeSumAverage();
    output[12]= computeSumEntropy();
    output[13]= computeSumVariance();

    output[14]= computeDifferenceEntropy();
    output[15]= computeDifferenceVariance();
    */
}


void printFeatures(double * features)
{
    std::cout << std::endl;
    std::cout << "ASM: " << features[0] << std::endl;
    std::cout << "AUTOCORRELATION: " << features[1] << std::endl;
    std::cout << "ENTROPY: " << features[2] << std::endl;
    std::cout << "MAXIMUM PROBABILITY: " << features[3] << std::endl;
    std::cout << "HOMOGENEITY: " << features[4] << std::endl;
    std::cout << "CONTRAST: " << features[5] << std::endl;

    std::cout << "CORRELATION: " << features[6] << std::endl;
    std::cout << "CLUSTER PROMINECENCE: " << features[7] << std::endl;
    std::cout << "CLUSTER SHADE: " << features[8] << std::endl;
    std::cout << "SUM OF SQUARES: " << features[9] << std::endl;
    std::cout << "IDM: " << features[10] << std::endl;

    /*
    std::cout << "SUM AVERAGE: " << features[11] << std::endl;
    std::cout << "SUM ENTROPY: " << features[12] << std::endl;
    std::cout << "SUM VARIANCE: " << features[13] << std::endl;

    std::cout << "DIFF ENTROPY: " << features[14] << std::endl;
    std::cout << "DIFF VARIANCE: " << features[15] << std::endl;
    */
}
