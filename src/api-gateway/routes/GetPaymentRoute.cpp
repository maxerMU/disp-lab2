#include "GetPaymentRoute.h"

#include <exceptions/server_exceptions.h>
#include <exceptions/logic_exceptions.h>
#include <logger/LoggerFactory.h>

#include "clients.h"

void GetPaymentRoute::Init(const IRequestHandlerContextPtr &context, const std::map<std::string, size_t> clients)
{
    m_context = std::dynamic_pointer_cast<ApiGatewayContext>(context);
    if (!m_context)
        throw ContextPtrCastException("get car route");

    m_clientsIndexes = clients;
}

void GetPaymentRoute::SetRequestParameters(const std::vector<std::string> &)
{
}

void GetPaymentRoute::ProcessRequest(const IRequestPtr &request, size_t &clientIndex)
{
    clientIndex = m_clientsIndexes[PAYMENTS_CLIENT];

    std::string paymentUid;
    if (m_context->GetRequestType() == ApiGatewayContext::GetRent)
        paymentUid = m_context->GetProcessInfo().getRentRequest.rent.paymentUid;
    
    if (paymentUid.empty())
        throw UndefinedPaymentUidException("get payment route");

    request->copy(m_context->GetCurrentRequest());
    request->SetTarget(GET_PAYMENT_BASE_TARGET + "/" + paymentUid);
}

void GetPaymentRoute::ProcessResponse(const IResponsePtr &responseFromClient)
{
    if (responseFromClient->GetStatus() == net::CODE_404)
    {
        m_context->GetCurrentResponse()->SetStatus(net::CODE_404);
        return;
    }

    if (responseFromClient->GetStatus() != net::CODE_200)
    {
        m_context->GetCurrentResponse()->copy(responseFromClient);
        throw ProcessingResponseException("get payment route invalid code");
    }

    PaymentDTO payment;
    payment.FromJSON(responseFromClient->GetBody());

    if (m_context->GetRequestType() == ApiGatewayContext::GetRent)
        m_context->GetProcessInfo().getRentRequest.payment = payment;
}
