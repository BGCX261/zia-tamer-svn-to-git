#ifndef _ZIA_API_HTTPSTEP_H_
#define _ZIA_API_HTTPSTEP_H_

#include "defines.hpp"

_BOF_ZIA_API_

class IMessage;

/*!
 * \brief Http steps namespace
 *
 */
namespace HttpStep
{
    /*!
     * \brief Http steps
     *
     * \todo describe pties of all steps.
     */
    enum ID
    {
        /*!
         * \brief None
         */
        NONE = 0,

        /*!
         * \brief Input
         */
        IN,
        /*!
         * \brief Post input
         */
        IN_POST,

        /*!
         * \brief Pre parser
         */
        PARSER_PRE,
        /*!
         * \brief Parser
         */
        PARSER,
        /*!
         * \brief Post parser
         */
        PARSER_POST,

        /*!
         * \brief Pre execution
         */
        EXEC_PRE,
        /*!
         * \brief Execution
         */
        EXEC,
        /*!
         * \brief Post execution
         */
        EXEC_POST,

        /*!
         * \brief Pre rawer
         */
        RAWER_PRE,
        /*!
         * \brief Rawer
         */
        RAWER,
        /*!
         * \brief Post rawer
         */
        RAWER_POST,

        /*!
         * \brief Pre output
         */
        OUT_PRE,
        /*!
         * \brief output
         */
        OUT

    };

    /*!
     * \brief The callback type for http steps.
     *
     * It is a Callback to a any method of the form:
     *
     * \code
     * IStream *        ( IMessage &, IStream * )
     * \endcode
     */
    typedef zia::api::Callback_2p< IStream*, IMessage&, IStream* >  Callback;

    /*!
     * \brief Association of a HttpStep::Callback and a http step.
     */
    class Pair
    {
    public:
        /*!
         * \brief The ID of the http step associated with the Callback.
         */
        HttpStep::ID        mStep;

        /*!
         * \brief The callback to call on the step \a mStep.
         */
        HttpStep::Callback  mCallback;

        /*!
         * \brief Constructor.
         *
         * \param stepId Where to hook the \a callback.
         * \param callback The callback to call.
         */
        Pair(HttpStep::ID stepId, HttpStep::Callback callback)
            : mStep(stepId), mCallback(callback)
        { }

    };
}

_EOF_ZIA_API_

#endif /* _ZIA_API_HTTPSTEP_H_ */
