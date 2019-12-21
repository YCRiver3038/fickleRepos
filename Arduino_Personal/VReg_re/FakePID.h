/*
 * FakePID.h
 * (疑似かもしれない)PID制御用の宣言・実装類
 */

#ifndef FAKEPID_HEADER_INCLUDED
#define FAKEPID_HEADER_INCLUDED

#define GAIN_DIFF_DEFAULT 0.6f
#define GAIN_PROP_DEFAULT 0.6f
#define GAIN_INTEG_DEFAULT 0.0001f
#define INTEG_RESET_COUNT_DEFAULT 10000

#define FPID_EL_REACHED_LIMIT 0xFFFFFFFF
#define FPID_EL_UNDER_LIMIT 0x00000000

/*
 * 構造体・メンバ説明
 * FPID_GainSet：PID制御のゲインを決める 
 * float GSetP：P(比例)ゲイン
 * float GSetI：I(積分)ゲイン
 * float GSetD：D(微分)ゲイン
 * int32_t resetCount：I制御に係る積算のリセットを行うタイミングの設定
 */
typedef struct
{
    float GSetP;
    float GSetI;
    float GSetD;
    int32_t resetCount;
}FPID_GainSet;

/*
 * クラス説明
 * FPIDConfig：設定されたPID制御のゲインの情報を格納する 
 * publicメンバ
 *  float PGain：P(比例)ゲイン
 *  float IGain：I(積分)ゲイン
 *  float DGain：D(微分)ゲイン
 *  int32_t integResetCount：I制御に係る積算のリセットを行うタイミングの設定
 *  FPIDConfig()：コンストラクタ
 *                マクロによって宣言された標準値に従ってゲインの設定をする
 *  FPIDConfig(FPID_GainSet gs)：コンストラクタ
 *                               引数"FPID_GainSet gs"によってゲインを設定する
 */
class FPIDConfig
{
    public:
        float PGain;
        float IGain;
        float DGain;
        int32_t integResetCount;
        
        FPIDConfig()
        {
            PGain = GAIN_PROP_DEFAULT;
            IGain = GAIN_INTEG_DEFAULT;
            DGain = GAIN_DIFF_DEFAULT;
            integResetCount = INTEG_RESET_COUNT_DEFAULT;
        }
        
        FPIDConfig(FPID_GainSet gs)
        {
            PGain = gs.GSetP;
            IGain = gs.GSetI;
            DGain = gs.GSetD;
            integResetCount = gs.resetCount;
        }
};

/*
 * クラス説明
 * FPIDController：制御対象にPID制御を行う 
 * publicメンバ：
 *  FPIDController()：コンストラクタ
 *                    privateメンバの初期化を行う
 *  control(FPIDConfig cnf, float aimVal, float observedVal, float* ctrlTarget)：PID制御を行う
 *      引数説明：
 *          FPIDConfig cnf：ゲインの情報
 *          float aimVal：制御目標値
 *          float observedVal：観測値
 *          float* ctrlTarget：操作対象変数へのポインタ(例：操作対象が float ct のとき &ctを渡す)
 *  extLimited(FPIDConfig cnfEL, float aimValEL, float observedValEL, float* ctrlTargetEL, float extLim)
 *      ：PID制御を行う他、観測値が上限を超えていないか確認する。上限を超えた場合、何もせず FPID_EL_REACHED_LIMIT を返す
 *      引数説明：
 *          FPIDConfig cnfEL：ゲインの情報
 *          float aimValEL：制御目標値
 *          float observedValEL：観測値
 *          float* ctrlTargetEL：操作対象変数へのポインタ(例：操作対象が float ct のとき &ctを渡す)
 *          float extLim：設定上限値
 *      返り値：
 *          FPID_EL_REACHED_LIMIT：上限に達した
 *          FPID_EL_UNDER_LIMIT：上限以下である
 * privateメンバ：
 *  float a2oDiff_P：1回前の操作における目標値と観測値の差
 *  float a2oDiff_N：目標値と観測値の差
 *  float IntDif：積算誤差(積分)
 *  int32_t IntDifCount：積算回数
 */
class FPIDController
{       
    private:
        float a2oDiff_P;
        float a2oDiff_N;
        float IntDif;
        int32_t IntDifCount;

    public:
        FPIDController()
        {
            a2oDiff_P = 0.0f;
            a2oDiff_N = 0.0f;
            IntDif = 0.0f;
            IntDifCount = 0;
        }
        
        void control(FPIDConfig cnf, float aimVal, float observedVal, float* ctrlTarget)
        {
            a2oDiff_P = a2oDiff_N;
            a2oDiff_N = aimVal - observedVal;
            IntDif += a2oDiff_N;
            *ctrlTarget += (a2oDiff_N*cnf.PGain)+((a2oDiff_P-a2oDiff_N)*cnf.DGain)+(IntDif*cnf.IGain);
            if(IntDifCount >= cnf.integResetCount)
            {
                IntDif = 0.0;
                IntDifCount = 0;
            }
        }
        
        uint32_t extLimited(FPIDConfig cnfEL, float aimValEL, float observedValEL, float* ctrlTargetEL, float extLim)
        {
            if(observedValEL > extLim)
            {
                return FPID_EL_REACHED_LIMIT;
            }
            else
            {
                control(cnfEL, aimValEL, observedValEL, ctrlTargetEL);
                return FPID_EL_UNDER_LIMIT;
            }
        }
};
#endif