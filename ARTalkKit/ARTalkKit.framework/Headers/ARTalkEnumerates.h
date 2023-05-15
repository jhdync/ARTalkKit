//
//  ARTalkEnumerates.h
//  ARTalkKit
//
//  Created by 余生 on 2022/3/18.
//

#ifndef ARTalkEnumerates_h
#define ARTalkEnumerates_h

/**
登录相关错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkLoginErrorCode) {
    
    /**
    0: 登录成功。没有错误。
     */
    ARTalkLoginErrorOk = 0,
    
    /**
     1: 登录失败。原因未知。
     */
    ARTalkLoginErrorUnknown = 1,
    
    /**
     2: 登录被服务器拒绝。
     */
    ARTalkLoginErrorRejected = 2,
    
    /**
     3: 登录参数无效。
     */
    ARTalkLoginErrorInvalidArgument = 3,
    
    /**
     4: App ID 无效。
     */
    ARTalkLoginErrorInvalidAppId = 4,
    
    /**
     5: Token 无效。
     */
    ARTalkLoginErrorInvalidToken = 5,
    
    /**
     6: Token 已过期，登录被拒绝。
     */
    ARTalkLoginErrorTokenExpired = 6,
    
    /**
     7: 登录未经授权。
     */
    ARTalkLoginErrorNotAuthorized = 7,
    
    /**
     8: 用户已登录，或正在登录 anyRTC云平台对讲系统，或未调用 logoutWithCompletion 方法退出 ARTalkConnectionStateAborted 状态。
     */
    ARTalkLoginErrorAlreadyLogin = 8,
    
    /**
     9: 登录超时。目前的超时设置为 12 秒。
     */
    ARTalkLoginErrorTimeout = 9,
    
    /**
     10: 登录过于频繁。方法 loginByToken 的调用频率超过 2 次／秒的上限。
     */
    ARTalkLoginErrorLoginTooOften = 10,
    
    /**
     101: SDK 未完成初始化。
     */
    ARTalkLoginErrorLoginNotInitialized = 101,
};

/**
登出错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkLogoutErrorCode) {

    /**
    0: 登出成功。
    */
    ARTalkLogoutErrorOk = 0,
    
    /**
    1: 预留错误码
    */
    ARTalkLogoutErrorRejected = 1,
    
    /**
    101: SDK 未完成初始化。
    */
    ARTalkLogoutErrorNotInitialized = 101,
    
    /**
    102: 登出 对讲系统前未调用 loginByToken 方法或者 loginByToken 方法调用未成功。
    */
    ARTalkLogoutErrorNotLoggedIn = 102,
};

/**
更新 token 相关错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkRenewTokenErrorCode) {
    
    /**
    0：更新 Token 成功。
    */
    ARTalkRenewTokenErrorOk = 0,
    
    /**
    1：更新 Token 失败。
    */
    ARTalkRenewTokenErrorFailure = 1,
    
    /**
    2：无效参数。
    */
    ARTalkRenewTokenErrorInvalidArgument = 2,
    
    /**
    3：预留错误码
    */
    ARTalkRenewTokenErrorRejected = 3,
    
    /**
    4：方法调用过于频繁。超过 2 次／秒上限。
    */
    ARTalkRenewTokenErrorTooOften = 4,

    /**
    5：输入 Token 已过期。
    */
    ARTalkRenewTokenErrorTokenExpired = 5,
    
    /**
    6：输入 Token 无效。
    */
    ARTalkRenewTokenErrorInvalidToken = 6,
    
    /**
    101: SDK 未完成初始化。
    */
    ARTalkRenewTokenErrorNotInitialized = 101,
    
    /**
    102: 更新 Token 前未调用 loginByToken 方法或者 loginByToken 方法调用未成功。
    */
    ARTalkRenewTokenErrorNotLoggedIn = 102,
};

/**
SDK 和 anyRTC 云平台对讲系统的连接状态。
 */
typedef NS_ENUM(NSInteger, ARTalkConnectionState) {
    
    /**
     1: 初始状态。SDK 未连接到 anyRTC云平台对讲系统。

     App 调用 loginByToken 方法后，SDK 开始登录 anyRTC云平台对讲系统，触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateConnecting 。
     */
    ARTalkConnectionStateDisconnected = 1,
    
    /**
    2: SDK 正在登录 anyRTC 云平台对讲系统。
     * 如果 SDK 登录成功，会触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateConnected 。
     * 如果 SDK 登录失败，会触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateDisconnected 。
     */
    ARTalkConnectionStateConnecting = 2,
    
    /**
     3: SDK 已登录 anyRTC云平台对讲系统。
     * 如果 SDK 由于网络原因断开与 anyRTC云平台对讲系统的连接，SDK 触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateReconnecting 。
     * 如果 SDK 由于重复登录而被服务器踢出，SDK 触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateAborted 。
     * 如果 App 调用 logoutWithCompletion 方法成功登出系统，SDK 触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateDisConnected 。
    */
    ARTalkConnectionStateConnected = 3,

    /**
     4: SDK 与 anyRTC云平台对讲系统连接由于网络原因出现中断，SDK 正在尝试自动重连 anyRTC云平台对讲系统。

     * 如果 SDK 登录成功，SDK 触发 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateConnected 。SDK 会自动加入中断时用户所在频道，并自动将本地用户属性同步到服务端。
     * 如果 SDK 登录失败，SDK 会保持 ARTalkConnectionStateReConnecting 状态，继续自动重连。
     */
    ARTalkConnectionStateReconnecting = 4,
    
    /**
     5: SDK 放弃登录 anyRTC 云平台对讲系统。

     可能原因：另一实例已经以同一用户 ID 登录 anyRTC云平台对讲系统。

     在此之后，SDK 需要调用 logoutWithCompletion 方法退出登录，再视情况调用 loginByToken 方法重新登录系统。
     */
    ARTalkConnectionStateAborted = 5,
};

/**
连接状态改变原因。
 */
typedef NS_ENUM(NSInteger, ARTalkConnectionChangeReason) {
    
    /**
     1: SDK 正在登录 anyRTC云平台对讲系统。
     */
    ARTalkConnectionChangeReasonLogin = 1,
    
    /**
     2: SDK 成功登录 anyRTC云平台对讲系统。
     */
    ARTalkConnectionChangeReasonLoginSuccess = 2,
    
    /**
     3: SDK 登录失败。
     */
    ARTalkConnectionChangeReasonLoginFailure = 3,
    
    /**
     4: SDK 未在 12 秒内登录 anyRTC云平台对讲系统，登录超时。可能原因：用户正处于 ARTalkConnectionStateAborted 状态或 ARTalkConnectionStateReconnecting 状态。
     */
    ARTalkConnectionChangeReasonLoginTimeout = 4,
    
    /**
     5: SDK 和 anyRTC云平台对讲系统的连接由于网络问题而断开超过 4 秒。
     */
    ARTalkConnectionChangeReasonInterrupted = 5,
    
    /**
     6: 用户已调用 logoutWithCompletion 方法登出 anyRTC云平台对讲系统。
     */
    ARTalkConnectionChangeReasonLogout = 6,
    
    /**
     7: 登录被 anyRTC云平台对讲服务器禁止。
     */
    ARTalkConnectionChangeReasonBannedByServer = 7,
    
    /**
     8: 本账号异地登录，本地断开连接。
     */
    ARTalkConnectionChangeReasonRemoteLogin = 8,
};

/**
用户加入频道相关错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkJoinChannelErrorCode) {
    
    /**
     0: 用户成功加入频道。
     */
    ARTalkJoinChannelErrorOk = 0,
    
    /**
     1: 用户加入频道失败。
     */
    ARTalkJoinChannelErrorFailure = 1,
    
    /**
     2: 预留错误码
     */
    ARTalkJoinChannelErrorRejected = 2,
    
    /**
     3: 用户无法加入频道。因为参数无效。
     */
    ARTalkJoinChannelErrorInvalidArgument = 3,
    
    /**
     4: 用户加入频道超时。当前的超时设置为 5 秒。可能原因：用户正处于 ARTalkConnectionStateAborted 状态或 ARTalkConnectionStateReconnecting 状态。
     */
    ARTalkJoinChannelErrorTimeout = 4,
    
    /**
     5: 同时加入的频道数超过 20 上限。
     */
    ARTalkJoinChannelErrorExceedLimit = 5,
    
    /**
     6: 用户正在加入频道或已成功加入频道。
     */
    ARTalkJoinChannelErrorAlreadyJoined = 6,
    
    /**
     7: 方法调用超过 50 次每 3 秒的上限。
     */
    ARTalkJoinChannelErrorTooOften = 7,
    
    /**
     8: 加入相同频道的频率超过每 5 秒 2 次的上限。
     */
    ARTalkJoinSameChannelErrorTooOften = 8,
    
    /**
     101: SDK 未完成初始化。
     */
    ARTalkJoinChannelErrorNotInitialized = 101,
    
    /**
     102: 用户加入频道前未调用 loginByToken 方法或者 loginByToken 方法调用未成功。
     */
    ARTalkJoinChannelErrorNotLoggedIn = 102,
};

/**
用户离开频道相关错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkLeaveChannelErrorCode) {
    
    /**
     0: 用户成功离开频道。
     */
    ARTalkLeaveChannelErrorOk = 0,
    
    /**
     1: 用户离开频道失败。
     */
    ARTalkLeaveChannelErrorFailure = 1,
    
    /**
     2: 预留错误码
     */
    ARTalkLeaveChannelErrorRejected = 2,
    
    /**
     3: 用户已不在频道内。
     */
    ARTalkLeaveChannelErrorNotInChannel = 3,
    
    /**
     101: SDK 未完成初始化。
     */
    ARTalkLeaveChannelErrorNotInitialized = 101,
    
    /**
     102: 用户在离开频道前未调用 loginByToken 方法或者 loginByToken 方法调用未成功。
     */
    ARTalkLeaveChannelErrorNotLoggedIn = 102,
};

/**
用户开始对讲错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkPushToTalkErrorCode) {
    /**
    0: 方法调用成功，或者更新操作成功
    */
    ARTalkPushToTalkErrorOK = 0,

    /**
    1: 用户对讲失败
    */
    ARTalkPushToTalkErrorFailure = 1,

    /**
    2: 参数错误
    */
    ARTalkPushToTalkErrorArgument = 2,

    /**
    3: **拒绝**
    */
    ARTalkPushToTalkErrorRejected= 3,

    /**
    4: 方法调用频率超过了每秒两次查询的限制
    */
    ARTalkPushToTalkErrorTooOften = 4,

    /**
    5: 对讲已存在
    */
    ARTalkPushToTalkErrorExisted = 5,

    /**
    6: 高级用户正在通话
    */
    ARTalkPushToTalkErrorRejectByPermission = 6,

    /**
    101: 对象未初始化
    */
    ARTalkPushToTalkErrorNotInitialized = 101,

    /**
    102: 未登录
    */
    ARTalkPushToTalkErrorUserNotLoginIn = 102,
    
    /**
    102: 未加入
    */
    ARTalkPushToTalkErrorChannelNotJoined = 103
};

/**
用户结束对讲错误码。
 */
typedef NS_ENUM(NSInteger, ARTalkPushToTalkEndErrorCode) {
    /**
     0: 方法调用成功，或者更新操作成功
     */
    ARTalkPushToTalkEndErrorCodeOK = 0,
    
    /**
     1: 对讲超时
     */
    ARTalkPushToTalkEndErrorCodeTimeOut = 1,
    
    /**
     2: 对讲被打断
     */
    ARTalkPushToTalkEndErrorCodeBreaked = 2,
    
    /**
     3: 对讲异常，例如网断了
     */
    ARTalkPushToTalkEndErrorCodeException= 3,
    
    /**
     3: 对讲不存在
     */
    ARTalkPushToTalkEndErrorCodeNotFound= 4
};

/**
 音频编解码器类型列表
 */
typedef NS_ENUM(NSInteger, ARTalkAduioCodecType) {
    /**
     * 1: OPUS
     */
    ARTalkAduioCodecOPUS = 1,
    /**
     * 8: AACLC
     */
    ARTalkAduioCodecAACLC = 8,
    /**
     * 9: HEAAC
     */
    ARTalkAduioCodecHEAAC = 9,
    /**
     * 19: AMR
     */
    ARTalkAduioCodecAMR = 20,
    /**
     * 20: AICODEC
     */
    ARTalkAduioCodecAICODEC = 20,
    /**
     * 253: GENERIC
     */
    ARTalkAduioCodecGENERIC = 253,
};

/**
 音频采样率
 */
typedef NS_ENUM(NSInteger, ARTalkAduioSampleRateType) {
    /** 8000: 8 kHz */
    ARTalkAduioSampleRate8000 = 8000,
    /** 16000: 16 kHz */
    ARTalkAduioSampleRate16000 = 16000,
    /** 44100: 44.1 kHz */
    ARTalkAduioSampleRate44100 = 44100,
    /** 48000: 48 kHz */
    ARTalkAduioSampleRate48000 = 48000,
};

#endif /* ARTalkEnumerates_h */
