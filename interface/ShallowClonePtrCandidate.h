#ifndef Candidate_ShallowClonePtrCandidate_h
#define Candidate_ShallowClonePtrCandidate_h
/** \class reco::ShallowClonePtrCandidate
 *
 * shallow clone of a particle candidate keepint a reference
 * to the master clone
 *
 * \author Luca Lista, INFN
 *
 * \version $Id: ShallowClonePtrCandidate.h,v 1.9 2007/06/13 16:31:37 llista Exp $
 *
 */
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/iterator_imp_specific.h"

namespace reco {
  class ShallowClonePtrCandidate : public Candidate {
  public:
    /// collection of daughter candidates
    typedef CandidateCollection daughters;
    /// default constructor
    ShallowClonePtrCandidate() : Candidate() {  }
    /// constructor from Particle
    explicit ShallowClonePtrCandidate( const CandidatePtr & masterClone ) : 
      Candidate( * masterClone ), 
      masterClone_( masterClone ) { 
    }
    /// constructor from values
    ShallowClonePtrCandidate( const CandidatePtr & masterClone, 
			   Charge q, const LorentzVector & p4, const Point & vtx = Point( 0, 0, 0 ) ) : 
      Candidate( q, p4, vtx ), masterClone_( masterClone ) { }
    /// destructor
    virtual ~ShallowClonePtrCandidate();
    /// returns a clone of the Candidate object
    virtual ShallowClonePtrCandidate * clone() const;
    /// first daughter const_iterator
    virtual const_iterator begin() const;
    /// last daughter const_iterator
    virtual const_iterator end() const;
    /// first daughter iterator
    virtual iterator begin();
    /// last daughter iterator
    virtual iterator end();
    /// number of daughters
    virtual size_t numberOfDaughters() const;
    /// return daughter at a given position (throws an exception)
    virtual const Candidate * daughter( size_type i ) const;
    /// return daughter at a given position (throws an exception)
    virtual Candidate * daughter( size_type i );
    /// has master clone pointer
    virtual bool hasMasterClonePtr() const;
    /// returns reference to master clone pointer
    virtual const CandidatePtr & masterClonePtr() const;

  private:
    // const iterator implementation
    typedef candidate::const_iterator_imp_specific<daughters> const_iterator_imp_specific;
    // iterator implementation
    typedef candidate::iterator_imp_specific<daughters> iterator_imp_specific;
    /// check overlap with another Candidate
    virtual bool overlap( const Candidate & c ) const { return masterClone_->overlap( c ); }
    /// CandidatePtrerence to master clone
    CandidatePtr masterClone_;
    /// post-read fixup operation
    virtual void fixup() const;
  };

}

#endif
