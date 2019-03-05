//
// Created by Sylvain Renevey on 1/25/2019.
//
/*! \class MexFunction
 *  \brief Class defining the entry point to get the EarthGRAM2016 atmospheric density from MATLAB.
 *
 * When called from MATLAB, the following inputs must be provided:
 * -# altitude (km).
 * -# latitude (degrees).
 * -# longitude (degrees).
 * -# char array containing the epoch. Must be in the format: 'YYYY-MM-DD hh:mm:ss'.

 *
 * The output argument is:
 * -# density (kg/m^3).
 *
 * MATLAB code example:
 *
 *     h = 20;
 *     lat = 30;
 *     lon = 120;
 * 	   epoch = '2019-01-25 14:30:00';
 *     density = get_atm_density(h, lat, lon, epoch);
 *
 */


#ifdef _WIN32
    #ifdef _WIN64
        #define TO_STRING_AUX( x )  #x
        #define TO_STRING( x )      TO_STRING_AUX( x )
        #define EARTHGRAM2016       TO_STRING( EARTHGRAM2016_PATH )
    #endif
#elif __APPLE__
    #define EARTHGRAM2016   EARTHGRAM2016_PATH
#elif __unix__
    #define EARTHGRAM2016   EARTHGRAM2016_PATH
#endif



#ifndef MEX_WRAPPER
#define MEX_WRAPPER

#include "mex.hpp"
#include "mexAdapter.hpp"
#include "Atmod1.h"

#endif //MEX_WRAPPER


using matlab::mex::ArgumentList;
using matlab::engine::convertUTF8StringToUTF16String;

class MexFunction : public matlab::mex::Function {
private:
    matlab::data::ArrayFactory                      m_factory;
    std::shared_ptr<matlab::engine::MATLABEngine>   m_matlabPtr;

public:
    /*! \fn MexFunction()
     *  \brief Public constructor of the class
     */
    MexFunction() {
        // Get pointer to engine
        m_matlabPtr = getEngine();
    }

    /*! \fn void operator()(ArgumentList outputs, ArgumentList inputs)
     *  \brief This method is called when the mex function is called from MATLAB.
     *
     *  \param outputs      ArgumentList containing the outputs of the program.
     *  \param inputs       ArgumentList containing the inputs of the program.
     *
     */
    void operator()(ArgumentList outputs, ArgumentList inputs) {
        checkArguments(outputs, inputs);

        // Read inputs in MATLAB Data API defined variables
        double h = inputs[0][0];
        double lat = inputs[1][0];
        double lon = inputs[2][0];
        const matlab::data::CharArray epoch_c_str = inputs[3];


        // Convert char array to string
        std::string epoch( epoch_c_str.toAscii() );

        // Get density
        Atm1 earth_gram_atm_model;
        earth_gram_atm_model.initdata(EARTHGRAM2016, "NameRef.txt", epoch);

        
        double pm1, density, tm1, um1, vm1, wm1, pp1, dp1, tp1, up1, vp1, wp1, ps1, ds1, ts1,
                us1, vs1, ws1, psmall, dsmall, tsmall, usmall, vsmall, wsmall, sos, sosp;
        int iupdate = 1;
        int initonce = 1;
        double time = 0.0;

        earth_gram_atm_model.traj(h, lat, lon, time, iupdate, initonce, &density, &pm1, &tm1, &um1, &vm1, &wm1,
                                     &dp1, &pp1, &tp1, &up1, &vp1, &wp1, &ds1, &ps1, &ts1, &us1, &vs1, &ws1, &dsmall,
                                     &psmall, &tsmall, &usmall, &vsmall, &wsmall, &sos, &sosp);


        // Create output
        outputs[0] = m_factory.createScalar<double>(density);
    }




    /*! \fn void checkArguments(ArgumentList outputs, ArgumentList inputs)
     *  \brief This method checks that 4 inputs have been passed in as arguments and are valid and that one output is retrieved.
     *
     *  \param outputs      ArgumentList containing the output of the program.
     *  \param inputs       ArgumentList containing the inputs of the program.
     *
     */
    void checkArguments(ArgumentList outputs, ArgumentList inputs) {

        // Check that four input arguments are passed
        if (inputs.size() != 4) {
            m_matlabPtr->feval(matlab::engine::convertUTF8StringToUTF16String("error"),
                             0, std::vector<matlab::data::Array>({ m_factory.createScalar("Four inputs are required.") }));
        }

        // Check first input argument
        if (inputs[0].getType() != matlab::data::ArrayType::DOUBLE ||
            inputs[0].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE ||
            inputs[0].getNumberOfElements() != 1)
        {
            m_matlabPtr->feval(convertUTF8StringToUTF16String("error"),
                             0, std::vector<matlab::data::Array>({ m_factory.createScalar("The first input must be a scalar.") }));
        }

        // Check second input argument
        if (inputs[1].getType() != matlab::data::ArrayType::DOUBLE ||
            inputs[1].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE ||
            inputs[1].getNumberOfElements() != 1)
        {
            m_matlabPtr->feval(convertUTF8StringToUTF16String("error"),
                             0, std::vector<matlab::data::Array>({ m_factory.createScalar("The second input must be a scalar.") }));
        }

        // Check third input argument
        if (inputs[2].getType() != matlab::data::ArrayType::DOUBLE ||
            inputs[2].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE ||
            inputs[2].getNumberOfElements() != 1)
        {
            m_matlabPtr->feval(convertUTF8StringToUTF16String("error"),
                             0, std::vector<matlab::data::Array>({ m_factory.createScalar("The third input must be a scalar.") }));
        }

        // Check fourth input argument
        if (inputs[3].getType() != matlab::data::ArrayType::CHAR)
        {
            m_matlabPtr->feval(convertUTF8StringToUTF16String("error"),
                             0, std::vector<matlab::data::Array>({ m_factory.createScalar("The fourth input must be an array of chars") }));
        }


        // Check number of outputs
        if (outputs.size() > 1) {
            m_matlabPtr->feval(convertUTF8StringToUTF16String("error"),
                             0, std::vector<matlab::data::Array>({ m_factory.createScalar("A single output is returned") }));
        }
    }
};