// Dear emacs, this is -*-c++-*-

#ifndef __ATHTAUSELECTORTOOL__
#define __ATHTAUSELECTORTOOL__

/**
   @class AthTauSelectorTool
   @brief Tool to select objects in Athena using an underlying pure ROOT tool.

   @author Karsten Koeneke (CERN)
   @date   April 2011

*/

// Include the interface
#include "ObjectSelectorCore/IAthSelectorTool.h"
#include "AthenaBaseComps/AthAlgTool.h"


// Forward declarations
namespace Root
{
class TTauSelectorTool
}


class AthTauSelectorTool
  : virtual public IAthSelectorTool,
            public AthAlgTool
{

public: 
  /** Standard constructor */
  AthTauSelectorTool( const std::string& type,
                          const std::string& name,
                          const IInterface* parent );


  /** Standard destructor */
  virtual ~AthTauSelectorTool();


public: 
  /** Gaudi Service Interface method implementations */
  virtual StatusCode initialize();

  /** Gaudi Service Interface method implementations */
  virtual StatusCode finalize();


  // Main methods
public:
  /** The main accept method: the actual cuts are applied here */
  const Root::TAccept& accept( const INavigable4Momentum* part );


  // Public methods
public:
  /** Method to get the underlying ROOT tool */
  inline Root::TTauSelectorTool* getRootTool() { return m_rootTool; };


  /** Method to get the plain TAccept */
  inline virtual const Root::TAccept& getTAccept( )
  {
    return this->getRootTool()->getTAccept();
  }


  // Private member variables
private:
  /** Pointer to the underlying ROOT based tool */
  Root::TTauSelectorTool* m_rootTool;

  /** A dummy return TAccept object */
  Root::TAccept m_acceptDummy;


}; // End: class definition


#endif

