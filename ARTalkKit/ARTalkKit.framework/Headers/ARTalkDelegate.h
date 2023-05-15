//
//  ARTalkDelegate.h
//  ARTalkKit
//
//  Created by 余生 on 2022/3/15.
//

#import <Foundation/Foundation.h>
#import "ARTalkEnumerates.h"

NS_ASSUME_NONNULL_BEGIN

@class ARTalkKit;
@class ARTalkChannel;

/**
 ARTalkDelegate 接口类向 App 发送回调通知，上报运行时的事件。
*/
@protocol ARTalkDelegate <NSObject>
@optional

/// 连接状态改变回调
/// @param kit ARTalkKit实例对象。
/// @param state 新的连接状态
/// @param reason 连接状态改变的原因
- (void)talkKit:(ARTalkKit * _Nonnull)kit connectionStateChanged:(ARTalkConnectionState)state reason:(ARTalkConnectionChangeReason)reason;

/// 网络状态变化
/// @param kit ARTalkKit实例对象。
/// @param upStatus 上行
/// @param downStatus 下行
- (void)talkKit:(ARTalkKit * _Nonnull)kit networkStatus:(int)upStatus status:(int)downStatus;

/// ptt 语音路径
/// @param kit ARTalkKit实例对象。
/// @param chanId 频道id
/// @param filePath 本地路径（enableLocalAudioRecord）
- (void)talkKit:(ARTalkKit * _Nonnull)kit recordFile:(NSString *)chanId path:(NSString *)filePath;

/// 本地音频数据回调
/// @param kit ARTalkKit实例对象。
/// @param chanId 频道id
/// @param data 数据
/// @param samples 音频帧的样本数量
/// @param sampleHz 采样率
/// @param channels 通道数
- (void)talkKit:(ARTalkKit * _Nonnull)kit localMicAudioData:(NSString *)chanId data:(NSData *)data samples:(NSInteger)samples sampleHz:(NSInteger)sampleHz channel:(NSInteger)channels;

/// 其它用户音频数据回调
/// @param kit ARTalkKit实例对象。
/// @param chanId 频道id
/// @param data 数据
/// @param samples 音频帧的样本数量
/// @param sampleHz 采样率
/// @param channels 通道数
- (void)talkKit:(ARTalkKit * _Nonnull)kit localSpeakerAudioData:(NSString *)chanId data:(NSData *)data samples:(NSInteger)samples sampleHz:(NSInteger)sampleHz channel:(NSInteger)channels;

/// （SDK 断线重连时触发）当前使用的对讲 Token 已超过 24 小时的签发有效期。
/// @param kit ARTalkKit实例对象。
- (void)talkKitTokenDidExpire:(ARTalkKit * _Nonnull)kit;

/**
 当前使用的对讲 Token 还有 30 秒过期。
 
 * SDK 触发该回调提醒 App 当前 Token 即将过期，应即时获取新 Token。收到该回调后，你需要在服务端生成新 Token 并调用 renewToken 方法将该 Token 传给 SDK。
 * 如果调用 loginByToken 方法登录时传入的 Token 直至过期仍未更新，SDK 会断线重连，用户将下线。

 @param kit 一个 ARTalkKit 实例。
 */
- (void)talkKitTokenPrivilegeWillExpire:(ARTalkKit *_Nonnull)kit;

@end

@protocol ARTalkChannelDelegate <NSObject>
@optional

/// 开始对讲回调
/// @param channel 所在频道。详见 ARTalkChannel 。
/// @param code 用户开始对讲错误码
- (void)channel:(ARTalkChannel * _Nonnull)channel pushToTalkResult:(ARTalkPushToTalkErrorCode)code;

/// 结束对讲回调
/// @param channel 所在频道。详见 ARTalkChannel 。
/// @param code 用户结束对讲错误码
- (void)channel:(ARTalkChannel * _Nonnull)channel pushToTalkEnded:(ARTalkPushToTalkEndErrorCode)code;

/// 其他用户开始对讲回调
/// @param channel 所在频道。详见 ARTalkChannel 。
/// @param uid 用户id
/// @param userData 自定义信息
/// @param level 用户对讲等级
- (void)channel:(ARTalkChannel * _Nonnull)channel userIsTalkOn:(NSString *)uid userData: (NSString * _Nullable)userData userLevel:(NSInteger)level;

/// 其他用户结束对讲回调
/// @param channel 所在频道。详见 ARTalkChannel 。
/// @param uid 用户id
/// @param userData 自定义信息
- (void)channel:(ARTalkChannel * _Nonnull)channel userIsTalkOff:(NSString *)uid userData: (NSString * _Nullable)userData;

/// 广播通道打开回调
/// @param channel 所在频道。详见 ARTalkChannel 。
/// @param uid 用户id
/// @param userData 自定义信息
- (void)channel:(ARTalkChannel * _Nonnull)channel userStreamOn:(NSString *)uid userData: (NSString * _Nullable)userData;

/// 广播通道关闭回调
/// @param channel 所在频道。详见 ARTalkChannel 。
/// @param uid 用户id
/// @param userData 自定义信息
- (void)channel:(ARTalkChannel * _Nonnull)channel userStreamOff:(NSString *)uid userData: (NSString * _Nullable)userData;

@end

NS_ASSUME_NONNULL_END
