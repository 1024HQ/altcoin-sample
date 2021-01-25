// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "1024 The Times 3/1/2021 Bitcoin 34k+ high price."; // แก้ไข 1
    const CScript genesisOutputScript = CScript() << ParseHex("edithere!") << OP_CHECKSIG; // แก้ไข 2 
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000; // แก้ไข 3 - Halving ทุก ๆ กี่บล็อก 
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb"); // แก้ไข 4
        consensus.BIP65Height = 0; // 
        consensus.BIP66Height = 0; // 
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ความยากสูงสุด
        consensus.nPowTargetTimespan = 2 * 60; // แก้ไข 5 - กี่นาทีจะทำการปรับค่าความยากใหม่  2*60 = 2 นาที
        consensus.nPowTargetSpacing = 1 * 60; // แก้ไข 6 - ความเร็วธุรกรรม หรือ ความเร็วที่จะเกิด block ใหม่
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6000; // 75% of 8000 เปลี่ยนกฎใหม่เมื่อมีการยอมรับบล็อกมากกว่า 6000 ปกติ bitcoin 51% โดยวัดจากช่วงการกำหนดเป้าหมาย
        consensus.nMinerConfirmationWindow = 8000; // nPowTargetTimespan / nPowTargetSpacing * 4 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1610514879; // 12:20 13/1/2021
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230768000; // 12:21 13/1/2021

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1230768001; // 12:22 13/1/2021
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1230768002; // 12:23 13/1/2021

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1230768003; // 12:24 13/1/2021
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1230768004; // 12:25 13/1/2021

        // ค่าความยากขั้นต่ำของระบบ
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");

        // signatures block ของฉัน
        consensus.defaultAssumeValid = uint256S("0xa456cbcdb353f731293091aeeaef686b23e912c23a80b8299f0a8fba2c169c8f"); // แก้ไข 7 - ปิดใช้งานการตรวจสอบ บล็อกที่เป็น signature ของเรา

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
		//แก้ไข 8 - ให้ตั้งเป็นอะไรก็ได้ 00-ff ข้างหลัง 0x เป็นเอกลักษณ์ของเราเอง โดยของผมจะใส่เป็น 1 0 2 4 ซึ่งก็คือ 31 30 32 34
        pchMessageStart[0] = 0x31; //1
        pchMessageStart[1] = 0x30; //0
        pchMessageStart[2] = 0x32; //2
        pchMessageStart[3] = 0x34; //4
        nDefaultPort = 5599; // แก้ไข 8 - port  
        nPruneAfterHeight = 100000; // ปิดใช้งานการแก้ไขบล็อกที่ต่ำกว่า 100000 เพราะส่วนใหญ่เริ่มต้นด้วยบล็อกว่างเปล่า 

		//สูตรสร้าง genesis hash เวลาunixtime nNonce bits version coin
        genesis = CreateGenesisBlock(1611479346, 257358, 0x1e0ffff0, 1, 50 * COIN); // แก้ไข 9
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb")); // แก้ไข 10
        assert(genesis.hashMerkleRoot == uint256S("0xa456cbcdb353f731293091aeeaef686b23e912c23a80b8299f0a8fba2c169c8f")); // แก้ไข 11

        // Node สำรองที่เชื่อถือได้  ใส่ ip หรือ โดเมนที่ชี้ไปยังเซิร์ฟเวอร์ Node  จะใส่เพิ่มกี่อันก็ได้
        vSeeds.emplace_back("node1.hi.in.th", true); // แก้ไข 12
		vSeeds.emplace_back("node2.hi.in.th", true); // แก้ไข 13

		// เป็นการกำหนดตัวอักษรนำหน้ารหัสต่าง ๆ เช่น publickey privatekey
		//https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0);// 1  แก้ไข 14
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,50);// M แก้ไข 15
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,51); // M แก้ไข 16
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,8); // 4 แก้ไข 17
        base58Prefixes[EXT_PUBLIC_KEY] = {0x31, 0x30, 0x32, 0x34}; //HEX ตัวอักษร 4 ตัว **แก้ หรือ ไม่ต้องแก้ก็ได้
        base58Prefixes[EXT_SECRET_KEY] = {0x34, 0x32, 0x30, 0x31; //HEX ตัวอักษร 4 ตัว  **แก้ หรือ ไม่ต้องแก้ก็ได้

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {  0, uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb")}, // แก้ไข 18
            }
        };

        chainTxData = ChainTxData{
			// getchaintxstats พิมพ์ใน console จะได้ข้อมูลมาใส่ ตรงนี้เอาไว้ใส่ทีหลังได้ เป็นบันทึกเช็คพ้อย ค่อยใส่ทีหลังได้เวลาอัพเดต QT
            1610516067, // * UNIX timestamp แก้ไข 19
            0,  // * total number of transactions between genesis and that timestamp
                    //   (the tx=... number in the SetBestChain debug.log lines)
            0.0     // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb"); //แก้ไข 20 ใส่ hash ของ block 0
        consensus.BIP65Height = 0; 
        consensus.BIP66Height = 0; 
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2 * 60; // แก้ไข 21
        consensus.nPowTargetSpacing = 1 * 60; // แก้ไข 22
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1500; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2020; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1610514879; // 12:20 13/1/2021
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1610514880; // 12:21 13/1/2021

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1610514881; // 12:22 13/1/2021
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1610514882; // 12:23 13/1/2021

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1610514883; // 12:23 13/1/2021
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1610514884; // 12:23 13/1/2021

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb"); //แก้ไข 23 - ใส่ blockhash 0


        pchMessageStart[0] = 0x31; //1
        pchMessageStart[1] = 0x30; //0
        pchMessageStart[2] = 0x32; //2
        pchMessageStart[3] = 0x34; //4
        nDefaultPort = 9955; //แก้ไข 24
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1611479346, 257358, 0x1e0ffff0, 1, 50 * COIN); //แก้ไข 25
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb")); //แก้ไข 26
        assert(genesis.hashMerkleRoot == uint256S("0xb10f4862b518bc6fdd5ad1bfe19a25326424770c307f3bbdb98ac7d8b069520a")); // แก้ไข 27

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet.hi.in.th", true); // แก้ไข 28

		// แนะนำว่าให้ไม่เหมือนกับ Mainnet ป้องกันความสับสน
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,50); //M แก้ไข 29
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0); // 1 แก้ไข 30
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,0); // 1 แก้ไข 31
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,45); //K แก้ไข 32
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; //**แก้ หรือ ไม่ต้องแก้ก็ได้
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};//**แก้ หรือ ไม่ต้องแก้ก็ได้

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x0e7bed63d6fb594c8991425daec2746bdc5acd0f2b3c2df4535747e7f0fcf3bb")}, //แก้ไข 33
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 
            1611479346, // แก้ไข 34
            0,
            0.0
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 200;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2 * 60; // แก้ไข 35
        consensus.nPowTargetSpacing = 1 * 60; // แก้ไข 36
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00"); //แก้ไข 37 ** ไม่จำเป็น

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); //แก้ไข 38 ** ไม่จำเป็น

        pchMessageStart[0] = 0xff; 
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0xbb;
        pchMessageStart[3] = 0xdd;
        nDefaultPort = 9999; //แก้ไข 39
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1610516753, 0, 0x207fffff, 1, 50 * COIN); //แก้ไข 40
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x70f88fae90608879be5a948505a5ece5b969d5ebc764053bfbf8861a2b0b455b")); //แก้ไข 41
        assert(genesis.hashMerkleRoot == uint256S("0xb10f4862b518bc6fdd5ad1bfe19a25326424770c307f3bbdb98ac7d8b069520a")); //แก้ไข 42

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x70f88fae90608879be5a948505a5ece5b969d5ebc764053bfbf8861a2b0b455b")}, //แก้ไข 43
            }
        };

        chainTxData = ChainTxData{
            0, 
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
