// CaliopeAnalysisElement.hh

#ifndef _CaliopeAnalysisElement_hh_
#define _CaliopeAnalysisElement_hh_

#include "ORDataProcessor.hh"
#include "ORSIS3302Decoder.hh"
#include <iostream>
#include <fstream>


class CaliopeAnalysisElement : public ORDataProcessor
{
  public:

    CaliopeAnalysisElement();

    virtual ~CaliopeAnalysisElement();

    virtual EReturnCode StartRun();
    virtual EReturnCode ProcessMyDataRecord(UInt_t* record);
    virtual EReturnCode EndRun();

  protected:
    ORSIS3302Decoder* fDecoder;
    ofstream fFile;
};

#endif
