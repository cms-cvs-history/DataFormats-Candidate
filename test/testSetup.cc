// $Id: testSetup.cc,v 1.1 2006/02/28 10:43:30 llista Exp $
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
    DummyCandidate( const LorentzVector & p, Charge q, const Point & v ) : reco::LeafCandidate( q, p, v ) { }
    virtual DummyCandidate * clone() const { return new DummyCandidate( * this ); }
  };
}

namespace test {
  struct DummySetup : public reco::Candidate::setup {
    DummySetup( const reco::Candidate::LorentzVector & p, reco::Candidate::Charge q, const reco::Candidate::Point & v ) : 
      reco::Candidate::setup( setupCharge( true ), setupP4( true ), setupVertex( true ) ) { 
      p4 = p; 
      charge = q;
      vertex = v;
    }
    void set( reco::Candidate& c ) { }
  };
}

CPPUNIT_TEST_SUITE_REGISTRATION(testSetup);

void testSetup::checkAll() {
  reco::Particle::LorentzVector p1( 1.0, 2.0, 3.0, 4.0 ), p2( 1.5, 2.5, 3.5, 4.5 );
  reco::Particle::Charge q1( 1 ), q2( -1 );
  reco::Particle::Point v1( 0.1, 0.2, 0.3 ), v2( 0.4, 0.5, 0.6 );
  test::DummyCandidate t( p1, q1, v1 );
  CPPUNIT_ASSERT( t.p4() == p1 );
  CPPUNIT_ASSERT( t.charge() == q1 );
  CPPUNIT_ASSERT( t.vertex() == v1 );

  test::DummySetup s( p2, q2, v2 );
  t.set( s );
  CPPUNIT_ASSERT( t.p4() == p2 );
  CPPUNIT_ASSERT( t.charge() == q2 );
  CPPUNIT_ASSERT( t.vertex() == v2 );
}
