#ifndef _ZIA_API_IMESSAGE_H_
#define _ZIA_API_IMESSAGE_H_

#include <string>

#include "defines.hpp"
#include "IStream.hpp"
#include "HttpStep.hpp"
#include "DataRep.hpp"
#include "ILog.hpp"

_BOF_ZIA_API_

/*!
 * \brief Callback used to handle FD r/w
 *
 * return false will reset the default system r/w.
 *
 * If used to read:
 *   1st arg : FD/HANDLE to read from.
 *   2nd arg : IStream to write on.
 *
 * If used to write:
 *   1st arg : FD/HANDLE to write on.
 *   2nd arg : IStream to read from.
 *
 */
typedef zia::api::Callback_2p< bool, int, IStream& >        FdCallback;

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
IMessage::IMessage();
IMessage::~IMessage();
bool                    IMessage::isParsed() const;
api::DataRep&           IMessage::http();
api::DataRep&           IMessage::httpResp();
api::DataRep&           IMessage::info();

//
// Minimal IMessage inherits implementation:
//
namespace zia {

class X : public api::IMessage
{
public:
    virtual ~X();

    virtual api::IMessage*  newMessageAtStep(api::HttpStep::ID stepId, api::IStream& input);
    virtual api::IStream*   newDataStream();
    virtual api::IStream*   newResourceStream(int FD,
                                              api::FdCallback readingCallback = api::FdCallback(),
                                              api::FdCallback writingCallback = api::FdCallback());
    virtual void            forceDeleteStream(api::IStream* stream);
    virtual void            setFdReadCallback(api::FdCallback callback = api::FdCallback());
    virtual void            setFdWriteCallback(api::FdCallback callback = api::FdCallback());
    virtual api::ILog&      log();

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
    IMessage();
    virtual ~IMessage();

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
     */
    api::DataRep&               httpResp();

    /*!
     * \brief Get message infos data
     */
    api::DataRep&               info();

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
     * \param FD The ressource to be handle by the IStream.
     * \param readingCallback If set, this will be used to read from the \a FD.
     * \param writingCallback If set, this will be used to write on the \a FD.
     * \return The IStream wrapping the \a FD.
     */
    virtual api::IStream*       newResourceStream(int FD,
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
     * \brief Set the input fd callback for reading.
     *
     * The FdCallback \a callback will be called when there
     * will be activity on the input FD of this message. Then,
     * the callback will read on the FD and write in the stream
     * recieved as an argument.
     *
     * \param callback The callback. Dont specify it to unset the callback.
     */
    virtual void                setFdReadCallback(api::FdCallback callback = api::FdCallback()) = 0;

    /*!
     * \brief Set the output fd callback for writing.
     *
     * The FdCallback \a callback will be called when the FD
     * will be available for writing. Then, the callback
     * will read on the stream and write on the FD.
     *
     * \param callback The callback. Dont specify it to unset the callback.
     */
    virtual void                setFdWriteCallback(api::FdCallback callback = api::FdCallback()) = 0;

    /*!
     * \brief Get the ILog.
     *
     * Used to log informations.
     */
    virtual api::ILog&          log() = 0;

protected:
    /*!
     * \brief true if is parsed.
     */
    bool                        mParsed;

    /*!
     * \brief Request http header data representation.
     */
    DataRep*                    mHttp;

    /*!
     * \brief Response http header data representation.
     */
    DataRep*                    mHttpResp;

    /*!
     * \brief Message info data representation.
     */
    DataRep*                    mInfo;

};

_EOF_ZIA_API_

#endif /* _ZIA_API_IMESSAGE_H_ */
