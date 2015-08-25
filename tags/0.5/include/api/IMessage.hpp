#ifndef _ZIA_API_IMESSAGE_H_
#define _ZIA_API_IMESSAGE_H_

#include <string>

#include "defines.hpp"
#include "IConnection.hpp"
#include "IStream.hpp"
#include "HttpStep.hpp"
#include "DataRep.hpp"
#include "ILog.hpp"

_BOF_ZIA_API_

/*!
 * \brief Manage entierly the current Message.
 *
 * Represente a http message entierly (request or response).
 * IMessage permits you to store all informations about this message,
 * and manipulate the execution flow ot it.
 *
 * \a http datas represents the datas in the http header.
 * \a info datas represents all others message informations.
 *
 * <h2> Zia core implementations: </h2>
 * \code

//
// Non-virtual IMessage members to implement:
//
IMessage::IMessage(api::IConnection& connection);
IMessage::~IMessage();
bool                    IMessage::isParsed() const;
api::DataRep&           IMessage::http();
api::DataRep&           IMessage::httpResp();
api::IConnection&       IMessage::connection();
api::ILog&              IMessage::log();

//
// Minimal IMessage inherits implementation:
//
namespace zia {

class X : public api::IMessage
{
public:
    X(api::IConnection& connection) ;
    virtual ~X();

    virtual api::IStream*       newDataStream();
    virtual api::IStream*       newResourceStream(
                                    api::Resource resource,
                                    api::FdCallback readingCallback = api::FdCallback(),
                                    api::FdCallback writingCallback = api::FdCallback()
                                );
    virtual void                forceDeleteStream(api::IStream* stream);
    virtual api::IMessage*      newMessageAtStep(api::HttpStep::ID stepId, api::IStream& input);

};

}

 * \endcode
 */
class IMessage
{
public:
    /*!
     * \brief Constructor.
     *
     */
    IMessage(api::IConnection& connection);
    virtual ~IMessage();

    IMessage(const IMessage&);
    IMessage&                   operator = (const IMessage&);

    /*!
     * \brief Check if the http header is parsed.
     *
     * \return true if the http header datas are ready for reading,
     * false if the http header is not yet totaly parsed.
     */
    bool                        isParsed() const;

    /*!
     * \brief Get request http header datas.
     */
    api::DataRep&               http();

    /*!
     * \brief Get response http header datas.
     *
     */
    api::DataRep&               httpResp();

    /*!
     * \brief Get the IConnection.
     */
    api::IConnection&           connection();

    /*!
     * \brief Get the ILog.
     *
     * Log about message.
     */
    api::ILog&                  log();


    /*!
     * \brief Create a data IStream.
     *
     * Data IStream means that you can write on it, and when
     * the stream aquire enought data, it call its Reader.
     *
     * \return A new IStream.
     */
    virtual api::IStream*       newDataStream() = 0;

    /*!
     * \brief Create a IStream which handle a system resource.
     *
     * Under unix/linux, \a FD will be a file descriptor.
     * Under Windows, \a FD will be an HANDLE (which is, int fact,  an \c int too).
     *
     * \param resource The ressource to be handle by the IStream.
     * \param readingCallback If set, this will be used to read from the \a FD.
     * \param writingCallback If set, this will be used to write on the \a FD.
     * \return The IStream wrapping the \a FD/HANDLE.
     */
    virtual api::IStream*       newResourceStream(api::Resource resource,
                                                  api::FdCallback readingCallback = api::FdCallback(),
                                                  api::FdCallback writingCallback = api::FdCallback()) = 0;

    /*!
     * \brief Force deletion of a IStream.
     *
     * Warning: the \a stream must not be used by something.
     * PS: Normal way to delete a stream is to close it.
     *
     * \param stream The IStream to delete.
     */
    virtual void                forceDeleteStream(api::IStream* stream) = 0;

    /*!
     * \brief Create a new message starting at a step.
     *
     * This create a new IMessage who has the same client but a
     * new exeuction flow started on \a stepId.
     * The \a input Stream will be send to the first callback of the step,
     * and the flow will continue normaly until the end.
     * Typicaly use to start a parallel repsone (eg: 100 reponses).
     *
     * The DataRep this->mHttp will be point on the same datas.
     * But this->mHttpResp will be duplicated in the new IMessage of
     * the new message.
     *
     * \param stepId The step where to begin the new flow.
     * \param input The input IStream send on the step.
     * \return The new IMessage of the new message, its state depends on where
     * you begin your response.
     */
    virtual api::IMessage*      newMessageAtStep(api::HttpStep::ID stepId, api::IStream& input) = 0;

protected:
    /*!
     * \brief IConnection pointer.
     *
     * Must be set.
     */
    IConnection&                mConnection;

    /*!
     * \brief true if is parsed.
     */
    bool                        mParsed;

    /*!
     * \brief IMessage's ILog.
     *
     * Must be set.
     */
    ILog*                       mLog;

    /*!
     * \brief Request http header data representation.
     *
     * Must be set.
     */
    DataRep*                    mHttp;

    /*!
     * \brief Response http header data representation.
     *
     * Must be set.
     */
    DataRep*                    mHttpResp;

};

_EOF_ZIA_API_

#endif /* _ZIA_API_IMESSAGE_H_ */
