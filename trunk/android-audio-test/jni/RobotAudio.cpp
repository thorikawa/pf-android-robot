#include "RobotAudio.h"
#include "log.h"

void RobotAudio::openFiles(WavInFile **inFile, WavOutFile **outFile)
{
  LOGD("openFiles");
  int bits, samplerate, channels;

  // open input file...
  *inFile = new WavInFile("/sdcard/poly.wav");

  // ... open output file with same sound parameters
  bits = (int)(*inFile)->getNumBits();
  samplerate = (int)(*inFile)->getSampleRate();
  channels = (int)(*inFile)->getNumChannels();

  *outFile = new WavOutFile("/sdcard/robot.wav", samplerate, bits, channels);
}



// Sets the 'SoundTouch' object up according to input file sound format & 
// command line parameters
void RobotAudio::setup(SoundTouch *pSoundTouch, const WavInFile *inFile, float pitch)

{
  LOGD("setup");
  int sampleRate;
  int channels;

  sampleRate = (int)inFile->getSampleRate();
  channels = (int)inFile->getNumChannels();
  pSoundTouch->setSampleRate(sampleRate);
  pSoundTouch->setChannels(channels);
  //pSoundTouch->setTempoChange(params->tempoDelta);
  pSoundTouch->setPitchSemiTones(pitch);
  //pSoundTouch->setRateChange(params->rateDelta);
  //pSoundTouch->setSetting(SETTING_USE_QUICKSEEK, params->quick);
  //pSoundTouch->setSetting(SETTING_USE_AA_FILTER, !(params->noAntiAlias));

  /*
  if (params->speech)
  {
      // use settings for speech processing
      pSoundTouch->setSetting(SETTING_SEQUENCE_MS, 40);
      pSoundTouch->setSetting(SETTING_SEEKWINDOW_MS, 15);
      pSoundTouch->setSetting(SETTING_OVERLAP_MS, 8);
      fprintf(stderr, "Tune processing parameters for speech processing.\n");
  }
  */
}




// Processes the sound
void RobotAudio::process(SoundTouch *pSoundTouch, WavInFile *inFile, WavOutFile *outFile)
{
  LOGD("process");
  int nSamples;
  int nChannels;
  int buffSizeSamples;
  SAMPLETYPE sampleBuffer[BUFF_SIZE];

  if ((inFile == NULL) || (outFile == NULL)) return;  // nothing to do.

  nChannels = (int)inFile->getNumChannels();
  assert(nChannels > 0);
  buffSizeSamples = BUFF_SIZE / nChannels;

  // Process samples read from the input file
  while (inFile->eof() == 0)
  {
      int num;

      // Read a chunk of samples from the input file
      num = inFile->read(sampleBuffer, BUFF_SIZE);
      nSamples = num / (int)inFile->getNumChannels();

      // Feed the samples into SoundTouch processor
      pSoundTouch->putSamples(sampleBuffer, nSamples);

      // Read ready samples from SoundTouch processor & write them output file.
      // NOTES:
      // - 'receiveSamples' doesn't necessarily return any samples at all
      //   during some rounds!
      // - On the other hand, during some round 'receiveSamples' may have more
      //   ready samples than would fit into 'sampleBuffer', and for this reason 
      //   the 'receiveSamples' call is iterated for as many times as it
      //   outputs samples.
      do 
      {
          nSamples = pSoundTouch->receiveSamples(sampleBuffer, buffSizeSamples);
          outFile->write(sampleBuffer, nSamples * nChannels);
      } while (nSamples != 0);
  }

  // Now the input file is processed, yet 'flush' few last samples that are
  // hiding in the SoundTouch's internal processing pipeline.
  pSoundTouch->flush();
  do 
  {
      nSamples = pSoundTouch->receiveSamples(sampleBuffer, buffSizeSamples);
      outFile->write(sampleBuffer, nSamples * nChannels);
  } while (nSamples != 0);
}

int RobotAudio::pitchShift(float pitch)
{
  LOGD("execute start");
  WavInFile *inFile;
  WavOutFile *outFile;
  SoundTouch soundTouch;

  try 
  {
      // Open input & output files
      openFiles(&inFile, &outFile);

      // Setup the 'SoundTouch' object for processing the sound
      setup(&soundTouch, inFile, pitch);

      // Process the sound
      process(&soundTouch, inFile, outFile);

      // Close WAV file handles & dispose of the objects
      delete inFile;
      delete outFile;

      fprintf(stderr, "Done!\n");
  } 
  catch (const runtime_error &e) 
  {
      // An exception occurred during processing, display an error message
      fprintf(stderr, "%s\n", e.what());
      return -1;
  }
  LOGD("execute end");
  return 0;
}