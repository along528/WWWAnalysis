#ifndef wwwAnalysis_Tau_H
#define wwwAnalysis_Tau_H

#include <D3PDReader/Event.h>

#include "wwwAnalysis/PhysicsObject.h"

namespace wwwAnalysis
{

  class Tau : public PhysicsObject
  {
    private:
      const D3PDReader::TauD3PDObjectElement *m_pD3PD;
    public:

      /*
       * Creates a Tau PhysicsObject
       */
      Tau(const D3PDReader::EventInfoD3PDObject &, const D3PDReader::TauD3PDObjectElement &);

      const D3PDReader::TauD3PDObjectElement &d3pd() const;
      
      ClassDef(Tau, 0);
  };

};



#endif
