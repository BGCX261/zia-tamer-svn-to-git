#ifndef _ZIA_API_HTTPSTEP_H_
#define _ZIA_API_HTTPSTEP_H_

#include "defines.hpp"
#include "Callback.hpp"
#include "IStream.hpp"

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
     */
    enum ID
    {
        /*!
         * \brief None
         *
         * NOP
         */
        NONE = 0,

        /*!
         * \brief Input
         *
         * - <tt>quand          :</tt> nouvelle connection
         * - <tt>inputStream    :</tt> socket
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> toute premiere etape
         * - <tt>exemple        :</tt> black liste,
         */
        IN,
        /*!
         * \brief Post input
         *
         * - <tt>quand          :</tt> juste apres IN
         * - <tt>inputStream    :</tt> sortie de IN
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> dechiffrement avec buffers,
         */
        IN_POST,

        /*!
         * \brief Pre parser
         *
         * - <tt>quand          :</tt> juste avant PARSER
         * - <tt>inputStream    :</tt> sortie de IN_POST
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> -
         */
        PARSER_PRE,
        /*!
         * \brief Parser
         *
         * - <tt>quand          :</tt> parser HTTP
         * - <tt>inputStream    :</tt> sortie de PARSER_PRE
         * - <tt>[outStream]    :</tt> http body / isParsed() == true
         * - <tt>description    :</tt> inutile ? peut etre
         * - <tt>exemple        :</tt> -
         */
        PARSER,
        /*!
         * \brief Post parser
         *
         * - <tt>quand          :</tt> nouvelle requete
         * - <tt>inputStream    :</tt> sortie de PARSER (http body)
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> chunked request, rewriting,
         */
        PARSER_POST,

        /*!
         * \brief Pre execution
         *
         * - <tt>quand          :</tt> juste avant l'execution
         * - <tt>inputStream    :</tt> sortie de PARSER_POST
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> decompression,
         */
        EXEC_PRE,
        /*!
         * \brief Execution
         *
         * - <tt>quand          :</tt> execution de la requete
         * - <tt>inputStream    :</tt> sortie de EXEC_PRE
         * - <tt>[outStream]    :</tt> reponse http body
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> CGI, cache,
         */
        EXEC,
        /*!
         * \brief Post execution
         *
         * - <tt>quand          :</tt> nouvelle reponse
         * - <tt>inputStream    :</tt> sortie de EXEC
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> compression,
         */
        EXEC_POST,

        /*!
         * \brief Pre rawer
         *
         * - <tt>quand          :</tt> juste avant RAWER
         * - <tt>inputStream    :</tt> sortie de EXEC_POST
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> chunked response,
         */
        RAWER_PRE,
        /*!
         * \brief Rawer
         *
         * - <tt>quand          :</tt> assemblage du header et du body de la reponse
         * - <tt>inputStream    :</tt> sortie de RAWER_POST
         * - <tt>[outStream]    :</tt> reponse message (raw data)
         * - <tt>description    :</tt> inutile ? peut etre
         * - <tt>exemple        :</tt> -
         */
        RAWER,
        /*!
         * \brief Post rawer
         *
         * - <tt>quand          :</tt> juste apres RAWER
         * - <tt>inputStream    :</tt> sortie de RAWER
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> dechiffrement avec buffers,
         */
        RAWER_POST,

        /*!
         * \brief Pre output
         *
         * - <tt>quand          :</tt> juste avant OUT
         * - <tt>inputStream    :</tt> sortie de RAWER_POST
         * - <tt>[outStream]    :</tt> -
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> -
         */
        OUT_PRE,
        /*!
         * \brief output
         *
         * - <tt>quand          :</tt> juste avant l'envoie
         * - <tt>inputStream    :</tt> sortie de OUT_PRE
         * - <tt>[outStream]    :</tt> raw data pour la socket
         * - <tt>description    :</tt> -
         * - <tt>exemple        :</tt> -
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
    typedef zia::api::Callback< IStream* (IMessage&, IStream*) >  Callback;

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
