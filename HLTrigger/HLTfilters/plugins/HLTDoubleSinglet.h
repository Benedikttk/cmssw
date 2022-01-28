#ifndef HLTDoubleSinglet_h
#define HLTDoubleSinglet_h

/** \class HLTDoubleSinglet
 *
 *
 *  This class is an HLTFilter (-> EDFilter) implementing a basic HLT
 *  trigger for pairs of object, evaluating all pairs with the first
 *  object from collection 1, and the second object from collection 2,
 *  cutting on variables relating to their 4-momentum representations.
 *  The object collections are assumed to be outputs of HLTSinglet
 *  single-object-type filters so that the access is thorugh
 *  RefToBases and polymorphic.
 *
 *
 *  \author Martin Grunewald
 *
 */

#include "DataFormats/Common/interface/Ref.h"
#include "HLTrigger/HLTcore/interface/HLTFilter.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include <string>
#include <vector>
namespace trigger {
  class TriggerFilterObjectWithRefs;
}

//
// class declaration
//

template <typename T1, typename T2, typename T3>
class HLTDoubleSinglet : public HLTFilter {
public:
  explicit HLTDoubleSinglet(const edm::ParameterSet&);
  ~HLTDoubleSinglet() override;
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  bool hltFilter(edm::Event&,
                 const edm::EventSetup&,
                 trigger::TriggerFilterObjectWithRefs& filterproduct) const override;

private:
  // configuration
  const std::vector<edm::InputTag> originTag1_;  // input tag identifying originals 1st product
  const std::vector<edm::InputTag> originTag2_;  // input tag identifying originals 2nd product
  const std::vector<edm::InputTag> originTag3_;  // input tag identifying originals 3rd product
  const edm::InputTag inputTag1_;                // input tag identifying filtered 1st product
  const edm::InputTag inputTag2_;                // input tag identifying filtered 2nd product
  const edm::InputTag inputTag3_;                // input tag identifying filtered 3rd product
  const edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> inputToken1_;
  const edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> inputToken2_;
  const edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> inputToken3_;
  const int triggerType1_;
  const int triggerType2_;
  const int triggerType3_;
  const double min_Dphi_, max_Dphi_;  // Delta phi (1,3) and (2,3) window
  const double min_Deta_, max_Deta_;  // Delta eta (1,3) and (2,3) window
  const double min_Minv_, max_Minv_;  // Minv(1,2) and Minv(2,3) window
  const double min_DelR_, max_DelR_;  // Delta R (1,3) and (2,3) window
  const double min_Pt_, max_Pt_;      // Pt(1,3) and (2,3) window
  const int min_N_;                   // number of triplets passing cuts required

  // calculated from configuration in c'tor
  const bool same12_, same13_, same23_;                                           // 1st and 2nd product are one and the same
  const bool cutdphi_, cutdeta_, cutminv_, cutdelr_, cutpt_;  // cuts are on=true or off=false

  //
  typedef std::vector<T1> T1Collection;
  typedef edm::Ref<T1Collection> T1Ref;
  typedef std::vector<T2> T2Collection;
  typedef edm::Ref<T2Collection> T2Ref;
  typedef std::vector<T3> T3Collection;
  typedef edm::Ref<T3Collection> T3Ref;
};

#endif  //HLTDoubleSinglet_h
