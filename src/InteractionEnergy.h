
#ifndef INTERACTIONENERGY_H_
#define INTERACTIONENERGY_H_


#include "general.h"
#include "Accessibility.h"
#include "ReverseAccessibility.h"

/**
 * Abstract utility class that covers necessary energy related functionalities
 * for the interaction energy computation given two RNAs.
 *
 * @author Martin Mann 2014
 *
 */
class InteractionEnergy {

public:
	/**
	 * Construct energy utility object given the accessibility ED values for
	 * two RNA sequences.
	 *
	 * @param accS1 accessibility of the first sequence
	 * @param accS2 accessibility of the second sequence (reversed to 3'-5'
	 *          index reading)
	 * @param maxInternalLoopSize1 maximal number of enclosed unpaired positions
	 *          between two intermolecular base pairs in sequence 1, ie it holds
	 *          for an intermolecular loop closed by base pairs (i1,i2) and
	 *          (j1,j2) : (j1-i1) <= (1+maxInternalLoopSize1)
	 * @param maxInternalLoopSize2 maximal number of enclosed unpaired positions
	 *          between two intermolecular base pairs in sequence 2, ie it holds
	 *          for an intermolecular loop closed by base pairs (i1,i2) and
	 *          (j1,j2) : (j2-i2) <= (1+maxInternalLoopSize2)
	 *
	 */
	InteractionEnergy( const Accessibility & accS1
			, const ReverseAccessibility & accS2
			, const size_t maxInternalLoopSize1
			, const size_t maxInternalLoopSize2
			);

	/**
	 * destruction
	 */
	virtual ~InteractionEnergy();


	/**
	 * Provides the overall energy for an interaction from [i1,j1] in the first
	 * sequence and [i2,j2] in the second sequence given the hybridization
	 * energy contribution.
	 *
	 * @param i1 the index of the first sequence interacting with i2
	 * @param j1 the index of the first sequence interacting with j2 with i1<=j1
	 * @param i2 the index of the second sequence interacting with i1
	 * @param j2 the index of the second sequence interacting with j1 with i2<=j2
	 * @param hybridE the hybridization energy for the interaction
	 *
	 * @return E = hybridE
	 * 				+ ED1(i1,j1) + ED2(i2,j2)
	 * 				+ Edangle(i1,i2) + Edangle(j1,j2)
	 * 				+ Eend(i1,i2) + Eend(j1,j2)
	 */
	virtual
	E_type
	getE( const size_t i1, const size_t j1
			, const size_t i2, const size_t j2
			, const E_type hybridE ) const;

	/**
	 * Checks whether or not two positions can for a base pair
	 * @param i1 index in first sequence
	 * @param i2 index in second sequence
	 * @return true if seq1(i1) can form a base pair with seq2(i2)
	 */
	virtual
	bool
	areComplementary( const size_t i1, const size_t i2 ) const;

	/**
	 * Computes the energy estimate for the interaction loop region closed by
	 * the intermolecular base pairs (i1,i2) and (j1,j2) where the regions
	 * [i1,j1] and [i2,j2] are considered unpaired or E_INF is the internal
	 * loop size exceeds the allowed maximum (see constructor).
	 *
	 * Note, the right interaction base pair (j1,j2) is not included in the
	 * returned energy value.
	 *
	 * @param i1 the index of the first sequence interacting with i2
	 * @param j1 the index of the first sequence interacting with j2 with i1<=j1
	 * @param i2 the index of the second sequence interacting with i1
	 * @param j2 the index of the second sequence interacting with j1 with i2<=j2
	 *
	 * @return the energy for the loop or E_INF if the allowed loop size is
	 *         exceeded
	 */
	virtual
	E_type
	getInterLoopE( const size_t i1, const size_t j1, const size_t i2, const size_t j2 ) const = 0;


	/**
	 * Computes the dangling end energy penalty estimate for the left side of
	 * an interaction loop region closed on the left by the intermolecular
	 * base pair (i1,i2).
	 *
	 * @param i1 the index of the first sequence interacting with i2
	 * @param i2 the index of the second sequence interacting with i1
	 *
	 * @return the dangling end penalty for the left side of the interaction
	 */
	virtual
	E_type
	getDanglingLeft( const size_t i1, const size_t i2 ) const = 0;


	/**
	 * Computes the dangling end energy penalty estimate for the right side of
	 * an interaction loop region closed on the right by the intermolecular
	 * base pair (j1,j2).
	 *
	 * @param j1 the index of the first sequence interacting with j2
	 * @param j2 the index of the second sequence interacting with j1
	 *
	 * @return the dangling end penalty for the right side of the interaction
	 */
	virtual
	E_type
	getDanglingRight( const size_t j1, const size_t j2 ) const = 0;

	/**
	 * Provides the penalty for closing an interaction with the given
	 * base pair on the "left side" (i1 = 5' end of seq1 of the interaction)
	 *
	 * @param i1 the index of the first sequence interacting with i2
	 * @param i2 the index of the second sequence interacting with i1
	 *
	 * @return the loop closure penalty for the left side of the interaction
	 */
	virtual
	E_type
	getEndLeft( const size_t i1, const size_t i2 ) const = 0;

	/**
	 * Provides the penalty for closing an interaction with the given
	 * base pair on the "right side" (j1 = 3' end of seq1 of the interaction)
	 *
	 * @param i1 the index of the first sequence interacting with i2
	 * @param i2 the index of the second sequence interacting with i1
	 *
	 * @return the loop closure penalty for the right side of the interaction
	 */
	virtual
	E_type
	getEndRight( const size_t j1, const size_t j2 ) const = 0;

	/**
	 * Access to the accessibility object of the first sequence
	 * (including sequence access)
	 * @return the accessibility object for the first sequence
	 */
	virtual
	const Accessibility &
	getAccessibility1() const;

	/**
	 * Access to the accessibility object of the second sequence
	 * (including sequence access)
	 * @return the reverse accessibility object for the second sequence
	 */
	virtual
	const ReverseAccessibility &
	getAccessibility2() const;

	/**
	 * Access to the maximal size of an unpaired stretch within seq1 within
	 * an interaction.
	 * @return the maximal internal loop size of an interaction for seq1
	 */
	const size_t getMaxInternalLoopSize1() const {
		return maxInternalLoopSize1;
	}

	/**
	 * Access to the maximal size of an unpaired stretch within seq2 within
	 * an interaction.
	 * @return the maximal internal loop size of an interaction for seq2
	 */
	const size_t getMaxInternalLoopSize2() const {
		return maxInternalLoopSize2;
	}

	/**
	 * Checks whether or not the given indices are valid index region within the
	 * sequence for an intermolecular loop and do not violate the maximal
	 * internal loop size.
	 * @param seq the sequence the indices correspond to
	 * @param i begin index of the region in the sequence
	 * @param j end index of the region in the sequence
	 * @param maxInternalLoopSize the maximally allowed distance of i and j, ie.
	 *        (j-i+1) <= maxInternalLoopSize
	 *
	 * @return true if the indices are fulfilling 0 <= i <= j < seq.length,
	 *           both sequence positions denote non-ambiguous nucleotides (!= N)
	 *           and (j-i+1) <= maxInternalLoopSize; false otherwise
	 */
	static
	bool
	isAllowedLoopRegion( const RnaSequence& seq, const size_t i, const size_t j, const size_t maxInternalLoopSize );

	/**
	 * Checks whether or not the given indices mark valid internal loop
	 * boundaries, i.e.
	 *  - (i1,i2) and (j1,j2) are complementary
	 *  - i1..j1 and i2..j2 are allowed loop regions
	 *  - no boundary overlap ( (j1-i1==0 && j2-i2==0) || (j1-i1>0 && j2-i2>0) )
	 *
	 * @param i1 the index of the first sequence interacting with i2
	 * @param j1 the index of the first sequence interacting with j2 with i1<=j1
	 * @param i2 the index of the second sequence interacting with i1
	 * @param j2 the index of the second sequence interacting with j1 with i2<=j2
	 *
	 * @return true if the boundaries are sound for internal loop calculation;
	 *         false otherwise
	 */
	bool
	isValidInternalLoop( const size_t i1, const size_t j1, const size_t i2, const size_t j2 ) const;

	/**
	 * Access to the normalized temperature for Boltzmann weight computation
	 */
	virtual
	E_type
	getRT() const = 0;


	/**
	 * Provides the best energy gain via stacking possible for this energy
	 * model
	 * @return the best stacking energy gain produced by getInterLoopE()
	 */
	virtual
	E_type
	getBestStackingEnergy() const = 0;

	/**
	 * Provides the best energy gain possible for interaction initiation
	 * for this energy model
	 * @return the best initiation energy gain produced by getInterLoopE()
	 */
	virtual
	E_type
	getBestInitEnergy() const = 0;

	/**
	 * Provides the best energy gain possible for left/right dangle
	 * for this energy model
	 * @return the best initiation energy gain produced by getDanglingLeft() or
	 *          getDanglingRight()
	 */
	virtual
	E_type
	getBestDangleEnergy() const = 0;

	/**
	 * Provides the best energy gain possible for left/right interaction ends
	 * for this energy model
	 * @return the best end energy gain produced by getEndLeft() or
	 *          getEndRight()
	 */
	virtual
	E_type
	getBestEndEnergy() const = 0;


	/**
	 * Provides the Boltzmann weight for a given energy.
	 * @param energ the energy the Boltzmann weight is to be computed for
	 * @return the Boltzmann weight, i.e. exp( - energy / RT );
	 */
	virtual
	E_type
	getBoltzmannWeight( const E_type energy ) const ;


protected:

	//! accessibility values for sequence S1
	const Accessibility & accS1;

	//! accessibility values for sequence S2 (reversed index order)
	const ReverseAccessibility & accS2;

	//! maximally allowed unpaired range between two base pairs in sequence S1
	//! forming an intermolecular internal loop
	const size_t maxInternalLoopSize1;

	//! maximally allowed unpaired range between two base pairs in sequence S2
	//! forming an intermolecular internal loop
	const size_t maxInternalLoopSize2;

};






#endif /* INTERACTIONENERGY_H_ */
