#ifndef TauAnalysis_ClassicSVfit_ClassicSVfitIntegrand_h
#define TauAnalysis_ClassicSVfit_ClassicSVfitIntegrand_h

#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#ifdef USE_SVFITTF
#include "TauAnalysis/SVfitTF/interface/HadTauTFBase.h"
#endif
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"

#include <Math/Functor.h>
#include <TMatrixD.h>
#include <TH1.h>
#include <TString.h>
#include <TFormula.h>

namespace classic_svFit
{
  class ClassicSVfitIntegrand
  {
   public:
    /// error codes that can be read out by ClassicSVfit class
    enum ErrorCodes {
      None            = 0x00000000,
      MatrixInversion = 0x00000001,
      LeptonNumber    = 0x00000010,
      TestMass        = 0x00000100
    };

    ClassicSVfitIntegrand(int);
    ~ClassicSVfitIntegrand();

    /// add an additional log(mTauTau) term to the nll to suppress high mass tail in mTauTau distribution (default is false)
    void addLogM_fixed(bool value, double power = 1.);
    void addLogM_dynamic(bool value, const std::string& power= "");
    
    void setDiTauMassConstraint(double diTauMass);
    void setTau1Constraint(bool tau1Constraint);  

    /// set pointer to histograms used to keep track of pT, eta, phi, mass and transverse mass of di-tau system
    /// during Markov Chain integration
    void setHistogramAdapter(HistogramAdapter* histogramAdapter);

    void setIdxLeg1_X(int idx);
    void setIdxLeg1_phi(int idx);
    void setIdxLeg1VisPtShift(int idx);
    void setIdxLeg1_mNuNu(int idx);
    void setIdxLeg2_X(int idx);
    void setIdxLeg2_phi(int idx);
    void setIdxLeg2VisPtShift(int idx);
    void setIdxLeg2_mNuNu(int idx);
    void setNumDimensions(unsigned numDimensions);

#ifdef USE_SVFITTF
    /// set transfer functions for pT of hadronic tau decays
    void setHadTauTF(const HadTauTFBase* hadTauTF);
    /// enable/disable use of transfer functions for hadronic tau decays
    void enableHadTauTF();
    void disableHadTauTF();

    /// set correlation between hadronic tau pT and MET
    void setRhoHadTau(double rhoHadTau);
#endif

    /// set momenta of visible tau decay products and of reconstructed missing transverse energy
    void setInputs(const std::vector<classic_svFit::MeasuredTauLepton>&, double, double, const TMatrixD&);

    /// evaluate integrand for given value of integration variables x
    double Eval(const double* x) const;

    /// static pointer to this (needed for interfacing the likelihood function calls to Markov Chain integration)
    static const ClassicSVfitIntegrand* gSVfitIntegrand;

   protected:
    /// measured tau leptons
    MeasuredTauLepton measuredTauLepton1_;
    bool leg1isLep_;
    double leg1Mass_;
    double leg1Mass2_;
    double leg1eX_x_;
    double leg1eX_y_;
    double leg1eX_z_;
    double leg1eY_x_;
    double leg1eY_y_;
    double leg1eY_z_;
    double leg1eZ_x_;
    double leg1eZ_y_;
    double leg1eZ_z_;
    MeasuredTauLepton measuredTauLepton2_;
    bool leg2isLep_;
    double leg2Mass_;
    double leg2Mass2_;
    double leg2eX_x_;
    double leg2eX_y_;
    double leg2eX_z_;
    double leg2eY_x_;
    double leg2eY_y_;
    double leg2eY_z_;
    double leg2eZ_x_;
    double leg2eZ_y_;
    double leg2eZ_z_;

    mutable double mVis_measured_;
    mutable double mVis2_measured_;

    Vector beamAxis_;

    /// measured MET
    double measuredMETx_;
    double measuredMETy_;

    /// inverse of MET covariance matrix
    TMatrixD invCovMET_;
    double invCovMETxx_;
    double invCovMETxy_;
    double invCovMETyx_;
    double invCovMETyy_;
    double const_MET_;

#ifdef USE_SVFITTF
    /// account for resolution on pT of hadronic tau decays via appropriate transfer functions
    const HadTauTFBase* hadTauTF1_;
    const HadTauTFBase* hadTauTF2_;
    bool useHadTauTF_;

    double rhoHadTau_;
#endif

    int idxLeg1_X_;
    int idxLeg1_phi_;
    int idxLeg1VisPtShift_;
    int idxLeg1_mNuNu_;
    int idxLeg2_X_;
    int idxLeg2_phi_;
    int idxLeg2VisPtShift_;
    int idxLeg2_mNuNu_;
    unsigned numDimensions_;

    /// flag to enable/disable addition of log(mTauTau) term to the nll to suppress high mass tail in mTauTau distribution
    bool addLogM_fixed_;
    double addLogM_fixed_power_;
    bool addLogM_dynamic_;
    TFormula* addLogM_dynamic_formula_;
    
    double diTauMassConstraint_ = -1.0;
    bool tau1Constraint_ = false;

    /// error code that can be passed on
    int errorCode_;

    HistogramAdapter* histogramAdapter_;

    /// verbosity level
    int verbosity_;
  };
}

#endif
