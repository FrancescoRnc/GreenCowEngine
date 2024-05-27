#pragma once

namespace Helpers
{
	template<typename T>
	class IObserver
	{
	public:
		virtual ~IObserver() {};
		virtual void Update(const T& subjectData) = 0;
	};

	template<typename T>
	class ISubject
	{
	public:
		virtual ~ISubject() {};
		virtual void Attach(IObserver<T>* observer) = 0;
		virtual void Detach(IObserver<T>* observer) = 0;
		virtual void Notify() = 0;
	};
}
