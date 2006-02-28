// $Id: testSetup.cc,v 1.4 2006/02/21 10:37:33 llista Exp $
#include <cppunit/extensions/HelperMacros.h>
#include "DataFormats/Candidate/interface/LeafCandidate.h"

class testSetup : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(testSetup);
  CPPUNIT_TEST(checkAll);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp() {}
  void tearDown() {}
  void checkAll(); 
};

namespace test {
  class DummyCandidate : public reco::LeafCandidate {
  public:
    DummyCandidate( const LorentzVector & p, Charge q = 0 ) : reco::LeafCandidate( q, p ) { }
    virtual DummyCandidate * clone() const { return new DummyCandidate( * this ); }
  };
}

namespace test {
  struct DummySetup : public reco::Candidate::setup {
    DummySetup( const reco::Candidate::LorentzVector & p, reco::Candidate::Charge q ) : 
      reco::Candidate::setup( setupCharge( true ), setupP4( true ) ) { 
      p4 = p; 
      charge = q;
    }
    void set( reco::Candidate& c ) { }
  };
}

CPPUNIT_TEST_SUITE_REGISTRATION(testSetup);

void testSetup::checkAll() {
  reco::Particle::LorentzVector p1( 1.0, 2.0, 3.0, 4.0 ), p2( 1.5, 2.5, 3.5, 4.5 );
  reco::Particle::Charge q1( 1 ), q2( -1 );
  test::DummyCandidate t( p1, q1 );
  CPPUNIT_ASSERT( t.p4() == p1 );
  CPPUNIT_ASSERT( t.charge() == q1 );

  test::DummySetup s( p2, q2 );
  t.set( s );
  CPPUNIT_ASSERT( t.p4() == p2 );
  CPPUNIT_ASSERT( t.charge() == q2 );
}
