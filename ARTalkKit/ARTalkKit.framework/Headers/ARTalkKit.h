//
//  ARTalkKit.h
//  ARTalkKit
//
//  Created by 余生 on 2022/3/15.
//

#import <Foundation/Foundation.h>
#import "ARTalkDelegate.h"
#import "ARTalkEnumerates.h"

@class ARTalkChannel;

/**-----------------------------------------------------------------------------
* @name  typedef about  ARTalkKit
* -----------------------------------------------------------------------------
*/

/**
 返回 loginByToken 方法的调用结果。errorCode: 登录错误码，详见 ARTalkLoginErrorCode 。
 */
typedef void (^ARTalkLoginBlock)(ARTalkLoginErrorCode errorCode);

/**
 返回 logoutWithCompletion 方法的调用结果。errorCode: 登出错误码，详见 ARTalkLogoutErrorCode 。
 */
typedef void (^ARTalkLogoutBlock)(ARTalkLogoutErrorCode errorCode);

/**
 返回 renewToken 方法的调用结果。
 * token: 新的 Token。
 * errorCode: 错误码。详见 ARTalkRenewTokenErrorCode 。
 */
typedef void (^ARTalkRenewTokenBlock)(NSString * _Nullable token, ARTalkRenewTokenErrorCode errorCode);

/**
 返回调用 joinWithCompletion 方法后返回。
 errorCode: 通过 ARTalkJoinChannelBlock 回调返回用户加入频道的结果，详见 ARTalkJoinChannelErrorCode 。
 */
typedef void (^ARTalkJoinChannelBlock)(ARTalkJoinChannelErrorCode errorCode);

/**
 调用 leaveWithCompletion 方法后返回。
 errorCode: 通过 ARTalkLeaveChannelBlock 回调返回用户离开频道的结果，详见 ARTalkLeaveChannelErrorCode 。
 */
typedef void (^ARTalkLeaveChannelBlock)(ARTalkLeaveChannelErrorCode errorCode);

NS_ASSUME_NONNULL_BEGIN

/**
 anyRTC 云平台对讲 频道方法。
 */
__attribute__((visibility("default"))) @interface ARTalkChannel: NSObject


/// ARTalkChannelDelegate 接口类向 App 发送回调通知，上报运行时的频道相关事件。
@property (nonatomic, weak, nullable) id<ARTalkChannelDelegate> channelDelegate;

/// 加入频道。
/// - Parameter completionBlock 同一用户只能同时加入最多 20 个频道。加入频道超限时用户会收到错误码 ARTalkJoinChannelErrorExceedLimit
- (void)joinWithCompletion:(ARTalkJoinChannelBlock _Nullable)completionBlock;

/// 离开频道。
/// - Parameter completionBlock ARTalkLeaveChannelBlock 回调返回本方法的调用结果。
- (void)leaveWithCompletion:(ARTalkLeaveChannelBlock _Nullable)completionBlock;

/// 设置自己的对讲等级
/// - Parameter level 说话等级，0为最大，level 越大等级越低
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setLevel:(int)level;

/// 获取自己的对讲等级
/// - returns 对讲等级
- (int)getLevel;

/// 设置推送音频质量
/// - Parameter nQuality: 1-5 低，中，高，超高，HD，默认为1
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setPushAudioQuality:(int)nQuality;

/// 设置拉取音频质量，暂不可使用
/// - Parameter nQuality: 1-5 低，中，高，超高，HD，默认为1
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setPullAudioQuality:(int)nQuality;

/// 开始对讲
/// - Parameter nTalkOnTime: 对讲时长，0为无限制
/// - returns 0方法调用成功，小于0方法调用失败
- (int)pushToTalk:(int)nTalkOnTime;

/// 结束对讲
/// - returns 0方法调用成功，小于0方法调用失败
- (int)stopPushToTalk;

/// 是否接收频道其它声音
/// - Parameter mute: mute YES 静音，NO 解除静音
/// - returns 0方法调用成功，小于0方法调用失败
- (int)muteAllRemoteAudio:(BOOL)mute;

/// 打断对讲
/// - returns 0方法调用成功，小于0方法调用失败
- (int)breakTalk;

/// 是否接收广播流
/// - Parameter enable: YES 接收，NO 不接收
/// - returns 0方法调用成功，小于0方法调用失败
- (int)enableAudioStream:(BOOL)enable;

/// 获取频道 ID
/// - returns 频道 ID
- (NSString *)getChannelId;

@end

@interface ARTalkKit : NSObject

- (instancetype _Nonnull)init NS_UNAVAILABLE;

/// ARTalkDelegate 接口类向 App 发送回调通知，上报运行时的事件。
@property (nonatomic, weak, nullable) id<ARTalkDelegate> talkDelegate;

/// 创建并初始化一个 ARTalkKit 实例。
/// - Parameters:
///   - appId: appId 如果你的开发包里没有 App ID，请向 anyRTC 云平台申请一个新的 App ID。
///   - delegate: ARTalkDelegate 向 App 发送回调通知，上报 anyRTC 云平台对讲 SDK 运行时的事件。
/// - returns 一个 ARTalkKit 实例。调用失败：nil。可能是因为 appId 的长度不是 32 个字符。
- (instancetype _Nullable)initWithAppId:(NSString * _Nonnull)appId
                              delegate:(id <ARTalkDelegate> _Nullable)delegate;

/// 释放当前 ARTalkKit 实例使用的所有资源。
/// - note 请不要在任何回调中调用该方法。
- (void)destroy;

/// 登录 anyRTC 云平台 对讲 系统。
/// - Parameters:
///   - token: 用于登录 anyRTC 云平台对讲系统的动态密钥。开启动态鉴权后可用。集成及测试阶段请将 token 设置为 nil 。
///   - uid: 登录 anyRTC 云平台对讲系统的用户 ID。 uid 必须为不超过 64 字节的字符串。请不要将 uid 设为空、 nil 或 “null"。
- (void)loginByToken:(NSString * _Nullable)token
                user:(NSString * _Nonnull)uid
          completion:(ARTalkLoginBlock _Nullable)completionBlock;

/// 登出 anyRTC 云平台对讲系统。
/// - Parameters: completionBlock 如果此方法调用成功，本地用户收到 ARTalkLogoutBlock 和 connectionStateChanged 回调，连接状态变为 ARTalkConnectionStateDisconnected。如果此方法调用失败，本地用户收到 ARTalkLoginBlock 回调。
- (void)logoutWithCompletion:(ARTalkLogoutBlock _Nullable )completionBlock;

/// 更新当前的对讲 Token
/// - Parameters:
///   - token 新的对讲 Token
///   - completionBlock ARTalkRenewTokenBlock 回调返回更新当前 Token 的结果
/// - note 在收到 talkKitTokenDidExpire 回调时你需要调用此方法更新 Token。 ARTalkRenewTokenBlock 回调会返回 Token 更新的结果。该方法的调用频率为 2 次／秒。
/// - returns 0方法调用成功，小于0方法调用失败
- (int)renewToken:(NSString * _Nonnull)token completion:(ARTalkRenewTokenBlock _Nullable)completionBlock;

/// 音频编码参数接口
/// - Parameters:
///   - type: 音频编解码器类型列表
///   - rate: 音频采样率
///   - channel: 通道数
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setAudioEncodeParameter:(ARTalkAduioCodecType)type sampleRate:(ARTalkAduioSampleRateType)rate channels:(int)channel;

/// 设置默认推送音频质量
/// - Parameter nQuality: 1-5 低，中，高，超高，HD，默认为1
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setDefaultPushAudioQuality:(int)nQuality;

/// 设置默认拉取音频质量，暂不可使用
/// - Parameter nQuality: 1-5 低，中，高，超高，HD，默认为1
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setDefaultPullAudioQuality:(int)nQuality;

/// 打开/关闭音频采集模块接口
/// - Parameters: enable YES 打开，NO 关闭
/// - returns 0方法调用成功，小于0方法调用失败
- (int)enableAudioCapture:(BOOL)enable;

/// 开关音频录制模块
/// - Parameters:
///   - enable: enable YES 打开，NO 关闭
///   - filePath: 路径
/// - returns 0方法调用成功，小于0方法调用失败
- (int)enableLocalAudioRecord:(BOOL)enable path:(NSString * _Nonnull)filePath;

/// 开关本地录音音频数据回调
/// - Parameter enable: YES 打开，NO关闭
/// - returns 0方法调用成功，小于0方法调用失败
- (int)enableLocalMicDataCallback:(BOOL)enable;

/// 开关指定频道远程对讲音频数据回调
/// - Parameters:
///   - enable: YES 打开，NO 关闭
///   - channelId: 频道 ID
/// - returns 0方法调用成功，小于0方法调用失败
- (int)enableLocalSpeakerDataCallback:(BOOL)enable channelId:(NSString * _Nonnull)channelId;

/// 设置推送音量
/// - Parameter volume: 音量 [0 , 400]
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setPushAudioVolume:(int)volume;

/// 设置播放音量
/// - Parameter volume: 音量 [0 , 400]
/// - returns 0方法调用成功，小于0方法调用失败
- (int)setPlayAudioVolume:(int)volume;

/// 通过 JSON 配置 SDK 提供技术预览或特别定制功能。
/// - Parameters: parameters JSON 格式的 SDK 选项。
/// - returns 0方法调用成功，小于0方法调用失败
/// - note JSON 选项默认不公开。详情请联系hi@dync.cc。
- (int)setParameters:(NSString * _Nonnull)parameters;

/// 创建一个 anyRTC 云平台对讲频道。
/// - Parameters:
///   - channelId 标识 anyRTC 云平台对讲通话的频道名称。channelId 必须为不超过 64 字节的字符串，不能为空、nil，或设为 “null"。
///   - delegate ARTalkChannelDelegate 接口类向 App 发送回调通知，上报运行时的频道相关事件。
/// - returns 调用成功：一个 ARTalkChannel 实例。调用失败：nil。可能是因为 channelId 无效，channelId 已存在。
/// - note 一个 ARTalkKit 实例中可以创建多个频道，但是同一个用户只能同时加入最多 20 个频道。请在不使用某个频道时，调用 releaseChannelWithId 方法销毁频道实例。
- (ARTalkChannel * _Nullable)createChannelWithId:(NSString * _Nonnull)channelId
                                    delegate:(id <ARTalkChannelDelegate> _Nullable)delegate;

/// 释放一个 ARTalkChannel 本地频道占用的所有资源。
/// - Parameters channelId  待释放的频道实例的 ID
/// - returns YES方法调用成功，NO方法调用失败
- (BOOL)releaseChannelWithId: (NSString * _Nonnull)channelId;

/** 设置日志文件路径

设置 SDK 的输出 log 文件。SDK 运行时产生的所有 log 将写入该文件。 App 必须保证指定的目录存在而且可写。

**Note**

 - 日志文件的默认地址如下:
   - iOS: `App Sandbox/Library/caches/ar_talk_sdk.log`
   - macOS
     - 开启沙盒: `App Sandbox/Library/Logs/ar_talk_sdk.log`, 例如 `/Users/<username>/Library/Containers/<App Bundle Identifier>/Data/Library/Logs/ar_talk_sdk.log`.
     - 关闭沙盒: `～/Library/Logs/ar_talk_sdk.log`.
 - 如需调用本方法，请在调用 initWithAppId 方法初始化 ARTalkKit 对象后立即调用，否则可能造成输出日志不完整。

 @param logFile 日志文件的完整路径。该日志文件为 UTF-8 编码。

 @return 0方法调用成功，小于0方法调用失败
 */
- (int)setLogFile:(NSString * _Nonnull)logFile;

/// 设置日志文件大小
/// @param fileSize 指定 SDK 输出日志文件的内存大小，单位为 KB。
/// @return 0方法调用成功，小于0方法调用失败，有可能是因为传入的参数无效
- (int)setLogFileSize:(int)fileSize;

/// 设置日志输出等级
/// @param filter 日志输出等级，详见 ARTalkLogFilter。
/// @return 0方法调用成功，小于0方法调用失败
- (int)setLogFilters:(int)filter;

/// 查询 SDK 版本号
/// @return 当前的对讲 SDK 版本号，格式为字符串，如 1.0.0.0
+ (NSString *_Nonnull)getSDKVersion;

@end

NS_ASSUME_NONNULL_END
