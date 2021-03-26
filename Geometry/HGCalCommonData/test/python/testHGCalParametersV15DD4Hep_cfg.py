import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Phase2C11_dd4hep_cff import Phase2C11_dd4hep

process = cms.Process("HGCalParametersTest",Phase2C11_dd4hep)
process.load("SimGeneral.HepPDTESSource.pdt_cfi")
process.load("Geometry.HGCalCommonData.hgcalV15ParametersInitialization_cfi")
process.load('FWCore.MessageService.MessageLogger_cfi')

if hasattr(process,'MessageLogger'):
    process.MessageLogger.HGCalGeom=dict()

process.DDDetectorESProducer = cms.ESSource("DDDetectorESProducer",
                                            confGeomXMLFiles = cms.FileInPath('Geometry/HGCalCommonData/data/dd4hep/testHGCalV15.xml'),
                                            appendToDataLabel = cms.string('')
                                            )

process.DDCompactViewESProducer = cms.ESProducer("DDCompactViewESProducer",
                                                 appendToDataLabel = cms.string('')
)

process.load("IOMC.RandomEngine.IOMC_cff")
process.RandomNumberGeneratorService.generator.initialSeed = 456789

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.generator = cms.EDProducer("FlatRandomEGunProducer",
    PGunParameters = cms.PSet(
        PartID = cms.vint32(14),
        MinEta = cms.double(-3.5),
        MaxEta = cms.double(3.5),
        MinPhi = cms.double(-3.14159265359),
        MaxPhi = cms.double(3.14159265359),
        MinE   = cms.double(9.99),
        MaxE   = cms.double(10.01)
    ),
    AddAntiParticle = cms.bool(False),
    Verbosity       = cms.untracked.int32(0),
    firstRun        = cms.untracked.uint32(1)
)

process.hgcalEEParametersInitialize.fromDD4Hep = cms.bool(True)
process.hgcalHESiParametersInitialize.fromDD4Hep = cms.bool(True)
process.hgcalHEScParametersInitialize.fromDD4Hep = cms.bool(True)

process.testEE = cms.EDAnalyzer("HGCalParameterTester",
                                Name = cms.untracked.string("HGCalEESensitive"),
                                Mode = cms.untracked.int32(1)
)

process.testHESil = process.testEE.clone(
    Name = cms.untracked.string("HGCalHESiliconSensitive")
)

process.testHESci = process.testEE.clone(
    Name = cms.untracked.string("HGCalHEScintillatorSensitive"),
    Mode = cms.untracked.int32(2)
)
 
process.p1 = cms.Path(process.generator*process.testEE*process.testHESil*process.testHESci)
