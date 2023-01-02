// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>

#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>

#include <bignum.h>
#include <chainparams.h>
#include <kernel.h>

unsigned int GetNextTargetRequired(const CBlockIndex* pindexLast, bool fProofOfStake, const Consensus::Params& params)
{
    if (pindexLast == nullptr)
        return UintToArith256(params.powLimit).GetCompact(); // genesis block

    const CBlockIndex* pindexPrev = GetLastBlockIndex(pindexLast, fProofOfStake);
    if (pindexPrev->pprev == nullptr)
        return UintToArith256(params.bnInitialHashTarget).GetCompact(); // first block
    const CBlockIndex* pindexPrevPrev = GetLastBlockIndex(pindexPrev->pprev, fProofOfStake);
    if (pindexPrevPrev->pprev == nullptr)
        return UintToArith256(params.bnInitialHashTarget).GetCompact(); // second block

    int64_t nActualSpacing = pindexPrev->GetBlockTime() - pindexPrevPrev->GetBlockTime();

    // pozoqo: target change every block
    // pozoqo: retarget with exponential moving toward target spacing
         CBigNum bnNew;
       //  bnNew = arith_uint512(arith_uint256().SetCompact(pindex->nBits));
        bnNew.SetCompact(pindexPrev->nBits);
    if (Params().NetworkIDString() != CBaseChainParams::REGTEST) {
        int64_t nTargetSpacing;

        if (fProofOfStake) {
            nTargetSpacing = params.nStakeTargetSpacing;
        } else {
            if (IsProtocolV09(pindexLast->nTime)) {
                nTargetSpacing = params.nStakeTargetSpacing * 6;
            } else {
                nTargetSpacing = std::min(params.nTargetSpacingWorkMax, params.nStakeTargetSpacing * (1 + pindexLast->nHeight - pindexPrev->nHeight));
            }
        }

        int64_t nInterval = params.nTargetTimespan / nTargetSpacing;
        bnNew *= ((nInterval - 1) * nTargetSpacing + nActualSpacing + nActualSpacing);
        bnNew /= ((nInterval + 1) * nTargetSpacing);
        }

    if (bnNew > CBigNum(params.powLimit))
        bnNew = CBigNum(params.powLimit);

    if (pindexLast->nHeight + 1 >= params.nTHeight) {
      return pozoqo(pindexLast, fProofOfStake, params);
     }
    return bnNew.GetCompact();
}

unsigned int pozoqo(const CBlockIndex* pindexLast, bool fProofOfStake, const Consensus::Params& params)
{

    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    int64_t nPastBlocks = params.nTpozoqo;

    // make sure we have at least (nPastBlocks + 1) blocks, otherwise just return powLimit
    if (!pindexLast || pindexLast->nHeight < nPastBlocks) {
        return bnPowLimit.GetCompact();
    }


    const CBlockIndex* pindexPrev = GetLastBlockIndex(pindexLast, fProofOfStake);
    const CBlockIndex *pindex = pindexLast;
    arith_uint512 bnPastTargetAvg;
	for (unsigned int nCountBlocks = 1; nCountBlocks <= nPastBlocks; nCountBlocks++) {
		arith_uint512 bnTarget = arith_uint512(arith_uint256().SetCompact(pindex->nBits));
		if (nCountBlocks == 1) {
			bnPastTargetAvg = bnTarget;
		} else {
			// NOTE: that's not an average really...
			bnPastTargetAvg = (bnPastTargetAvg * nCountBlocks + bnTarget) / (nCountBlocks + 1);
		}

		if(nCountBlocks != nPastBlocks) {
			assert(pindex->pprev); // should never fail
			pindex = pindex->pprev;
		}
	}
          int64_t nTargetSpacing;
        if (fProofOfStake) {
            nTargetSpacing = params.nTpozoqo;
        }
	arith_uint512 bnNew(bnPastTargetAvg);
	int64_t nActualTimespan = pindexLast->GetBlockTime() - pindex->GetBlockTime();
	// NOTE: is this accurate? nActualTimespan counts it for (nPastBlocks - 1) blocks only...
       int64_t nTargetTimespan = nPastBlocks;
	if (nActualTimespan < nTargetTimespan)
		nActualTimespan = nTargetTimespan/0.01;
	if (nActualTimespan > nTargetTimespan*0.01)
		nActualTimespan = nTargetTimespan*0.01;

	// Retarget
	bnNew *= nActualTimespan;
	bnNew /= nTargetTimespan;
	arith_uint256 bnFinal = bnNew.trim256();
	if (bnFinal <= 0 || bnFinal > bnPowLimit) {
		bnFinal = bnPowLimit;
	}

	return bnFinal.GetCompact();
}


bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}
