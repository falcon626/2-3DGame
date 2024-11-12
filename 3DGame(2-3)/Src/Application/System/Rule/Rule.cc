#pragma once

// // // // // // // // // // //
// 設計書 兼 コーディング規約
// // // // // // // // // // //

namespace Demonstration
{
	class Example
	{
	public:
		enum class Species
		{
			Unknown,
			Hero,
			MagicCaster,
			Creature,
			All
		};

		explicit Example(const Math::Vector3& pos) { m_pos = pos; }
		~Example() = default;

	private:
		typedef struct tagParameter
		{
			int32_t  hp_    { Def::IntZero };
			uint32_t atkPow_{ Def::UIntZero };

			FLOAT32  dist_   { Def::FloatZero };
			double_t percent_{ Def::DoubleZero };
		}Parameter, &R_Parameter;

		typedef struct tagHeroParameter : public Parameter
		{
			uint32_t swordPow_;
		}HeroParameter, &R_HeroParameter;

		typedef struct tagMagicCasterParameter : public Parameter
		{
			uint32_t wandPow_;
			Parameter param_;
		}MagicCasterParameter, & R_MagicCasterParameter;

		typedef struct tagCreatureParameter : public Parameter
		{
			uint32_t physicalPow_;
			Parameter param_;
		}CreatureParameter, & R_CreatureParameter;

		typedef struct tagPlayer
		{
			Species type_;

			union
			{
				HeroParameter        _hero;
				MagicCasterParameter _magic;
				CreatureParameter    _creature;
			}param_;
		}Player, &R_Player;

		Math::Vector3 m_pos;
		Player m_player;
	};
}

/*
＜クラス内宣言順（先にパブリック　後にプライベート）＞

（シングルトンは例外）
・コンストラクタ
　　・引数付き（explicit）
　　・デフォルト
　　・コピー
・デストラクタ

（実行順）（可能な限りインライン化しautoで宣言,さらにnoexcept）
・メンバ関数
・仮想関数
・オーバーライド

（セッターはインスタンス時以外で使わない場合引数付きコンストラクタで済ます）
・セッター
・ゲッター

・ファンクタ
・その他（自分以外が使わない関数はprivateに入れる）

＜クラスメンバ定数・変数　宣言順番＞

（実体の大きさ順）
・コンテナ型
　　・list
　　・vector
　　・map
　　・unordered_map
　　・tuple
　　・pair
・配列
　　・array

（可能な限りスマートポインタ）
・クラス
・構造体
・ユニオン
　　・ユニークポインタ
　　・シェアードポインタ
　　・ウィークポインタ

・イント
・アンサインドイント
・ロング
・アンサインドロング
・ロングロング
・アンサインドロングロング

・フロート
・ダブル
・ロングダブル

＜命名規則＞

＃関数（単語毎に大文字始まり）（優先度順）

・セッター　Set
・boolを返すゲッター　Is
・ゲッター　Get

・事前処理　Pre
・事後処理　Post

・初期化　Init
・更新　　Update
・描画　　Draw

・削除　Kill
・起動　Trigger

・移動　Move
・方向　Dir
・速度　Speed
・方向と速度　Velocity

＃変数　定数　オブジェクト名（基本的に関数と同様）

・クラス名　　　MyClass
・クラスメンバ　m_val

・構造体名　　　tagStruct
　　　　　typedefでStructと参照型のR_Structを宣言
・構造体メンバ　val_

・共有体名　　　_tagUnion
　　　　　typedefでUnionと参照型のR_Unionを宣言
・共有体メンバ　_val

・グローバル変数　global_val
・ローカル変数　localVal

・グローバル、メンバ定数　ConstVal
・ローカル定数　localConstVal

（可能な限りMinではじめMaxで終えるなど最小と最大をわかりやすく）
・列挙型　MyNumbers
・列挙型Class　MyNumbers

・シェアードポインタ　sp
・ユニークポインタ　up
・ウィークポインタ　wp
・生ポインタ　p

・コンテナ　vals
*/